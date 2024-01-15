use std::path::{PathBuf, Path};

use crate::{
    buffer::{Buffer, Mode},
    editor::Editor,
    lines::Lines,
    render::Render,
    row::Row,
    size::RowCol,
};

trait LoadBackup {
    fn restore(&mut self);
    fn export(&self);
    fn import(&mut self, path: &Path);
}

trait MakeBackup {
    fn save(&self) -> BufferBackup;
}

impl LoadBackup for Editor {
    fn restore(&mut self) {
        todo!()
    }

    fn export(&self) {
        todo!()
    }

    fn import(&mut self, path: &Path) {
        todo!()
    }
}

impl MakeBackup for Editor {
    fn save(&self) -> BufferBackup {
        BufferBackup {
            content: self.buffer.content.clone(),
            path: self.buffer.path.clone(),
            mode: self.buffer.mode,
        }
    }
}

#[derive(Debug)]
struct BufferBackup {
    content: Lines,
    path: PathBuf,
    mode: Mode,
}

#[derive(Debug)]
pub struct History {
    inner: Vec<BufferBackup>,
}

impl History {
    pub fn new() -> Self {
        Self { inner: Vec::new() }
    }
}
