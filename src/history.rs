use std::{
    collections::VecDeque,
    fs::File,
    path::{Path, PathBuf},
};

use serde::{de::Visitor, ser::SerializeStruct, Deserialize, Serialize, Serializer};

use crate::{
    buffer::{Buffer, Mode},
    editor::Editor,
    lines::Lines,
    prelude::*,
    render::Render,
    row::Row,
    settings::{HISTORY_CAPACITY, HISTORY_FILE_NAME},
    size::RowCol,
};

trait LoadBackup {
    fn restore(&mut self, backup: BufferBackup);
}

trait MakeBackup {
    fn save(&self) -> BufferBackup;
}

impl LoadBackup for Buffer {
    fn restore(&mut self, backup: BufferBackup) {
        self.content = backup.content;
        self.mode = backup.mode;
        self.path = backup.path;
    }
}

impl MakeBackup for Buffer {
    fn save(&self) -> BufferBackup {
        BufferBackup {
            content: self.content.clone(),
            path: self.path.clone(),
            mode: self.mode,
        }
    }
}

#[derive(Debug, Serialize)]
pub struct BufferBackup {
    content: Lines,
    path: PathBuf,
    mode: Mode,
}

#[derive(Debug, Serialize)]
pub struct History {
    inner: VecDeque<BufferBackup>,
}

impl History {
    pub fn new() -> Self {
        Self {
            inner: VecDeque::with_capacity(HISTORY_CAPACITY),
        }
    }

    pub fn append(&mut self, backup: BufferBackup) -> InternalResult<()> {
        if self.inner.len() + 1 > HISTORY_CAPACITY {
            self.inner.pop_front();
        }
        self.inner.push_back(backup);
        Ok(())
    }

    pub fn pop(&mut self) -> InternalResult<BufferBackup> {
        match self.inner.pop_back() {
            Some(backup) => Ok(backup),
            None => Err(InternalError::FileNotFound),
        }
    }

    fn export(&self, workspace: &Path) -> AppResult<()> {
        if !workspace.exists() {
            return Ok(Err(InternalError::WorkspaceFolderDoesNotExists));
        }
        workspace.to_path_buf().push(HISTORY_FILE_NAME);
        if !workspace.exists() {
            return Ok(Err(InternalError::HistoryFileNotFund));
        };

        let history_file = File::open(workspace)?;

        serde_json::to_writer(history_file, &self.inner)?;

        Ok(Ok(()))
    }

    fn import(&mut self, path: &Path) -> IoResult<()> {
        todo!()
    }
}

impl Serialize for Lines {
    fn serialize<S>(&self, serializer: S) -> Result<S::Ok, S::Error>
    where
        S: serde::Serializer,
    {
        serializer.serialize_str(&self.to_string())
    }
}

#[cfg(test)]
mod tests {}
