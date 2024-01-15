use std::{
    fs::{self, File},
    io::{self, Write},
    path::{Path, PathBuf},
};

use crate::{error::AppResult, history::History, lines::Lines, prelude::*, row::Row};

pub trait OpenModes {
    fn open_read_only(path: &Path) -> InternalResult<File>;
    fn open_read_write(path: &Path) -> InternalResult<File>;
    fn open_create(path: &Path) -> InternalResult<File>;
}

#[derive(Debug, PartialEq, Eq, Clone, Copy)]
pub enum Mode {
    ReadOnly,
    ReadWrite,
    Create,
}

#[derive(Debug)]
/// store File data and more information
pub struct Buffer {
    pub path: PathBuf,
    pub format: String,
    pub file_name: String,
    pub mode: Mode,
    pub content: Lines,
    history: History,
}

impl Buffer {
    pub fn new() -> Self {
        Self {
            path: PathBuf::new(),
            format: String::new(),
            file_name: String::new(),
            content: Lines::new(),
            history: History::new(),
            mode: Mode::ReadWrite,
        }
    }

    pub fn open(&mut self, path: &Path, mode: Mode) -> AppResult<()> {
        match self.update_content(path)? {
            Ok(..) => (),
            Err(err) => return Ok(Err(err)),
        };

        self.update_info(path);

        self.path = path.to_path_buf();

        self.mode = mode;

        Ok(Ok(()))
    }

    pub fn save(&self) -> InternalResult<()> {
        match self.mode {
            Mode::ReadOnly => Err(InternalError::ReadOnlyBuffer),
            _ => {
                let mut file = Self::get_file(&self.path, self.mode)?;
                for row in self.content.iter() {
                    file.write(row.as_bytes());
                    file.write(&[b'\n']);
                }
                Ok(())
            }
        }
    }

    fn update_info(&mut self, path: &Path) {
        match path.file_name() {
            Some(name) => match name.to_os_string().into_string() {
                Ok(string) => self.file_name = string,
                Err(..) => self.file_name.clear(),
            },
            None => self.file_name.clear(),
        };

        match path.extension() {
            Some(name) => match name.to_os_string().into_string() {
                Ok(string) => self.format = string,
                Err(..) => self.format.clear(),
            },
            None => self.format.clear(),
        };
    }

    #[inline]
    fn get_file(path: &Path, mode: Mode) -> InternalResult<File> {
        match mode {
            Mode::ReadOnly => Self::open_read_only(path),
            Mode::ReadWrite => Self::open_read_write(path),
            Mode::Create => Self::open_create(path),
        }
    }

    fn update_content(&mut self, path: &Path) -> AppResult<()> {
        let mut file = match Buffer::get_file(path, self.mode) {
            Ok(file) => file,
            Err(err) => return Ok(Err(err)),
        };

        self.content = Lines::read(&mut file)?;

        Ok(Ok(()))
    }

    #[inline]
    pub fn push_empty_row(&mut self) {
        self.content.push_empty_row()
    }

    pub fn push_row_with_content(&mut self, content: String) {
        self.content.push_row_with_content(content)
    }

    fn write_to_end_row(&mut self) {}

    /// return perv / current / next row len
    fn get_row_info(&mut self, index: usize) -> (usize, usize, usize) {
        let perv = match self.get_row(index - 1) {
            Some(row) => row.len(),
            None => 0,
        };
        let current = match self.get_row(index) {
            Some(row) => row.len(),
            None => 0,
        };
        let next = match self.get_row(index + 1) {
            Some(row) => row.len(),
            None => 0,
        };
        (perv, current, next)
    }

    pub fn set_path(&mut self, path: PathBuf) {
        self.path = path;
    }

    pub fn get_row_len(&self, index: usize) -> usize {
        match self.content.get(index) {
            Some(row) => row.len(),
            None => 0,
        }
    }

    #[inline]
    pub fn get_row(&self, index: usize) -> Option<&Row> {
        self.content.get(index)
    }

    #[inline]
    pub fn get_mut_row(&mut self, index: usize) -> Option<&mut Row> {
        self.content.get_mut(index)
    }

    pub fn len(&self) -> usize {
        self.content.len()
    }
}

impl OpenModes for Buffer {
    fn open_read_only(path: &Path) -> InternalResult<File> {
        match File::options()
            .read(true)
            .write(false)
            .create(false)
            .open(path)
        {
            Ok(file) => Ok(file),
            Err(err) => match err.kind() {
                io::ErrorKind::NotFound => Err(InternalError::FileNotFound),
                io::ErrorKind::PermissionDenied => Err(InternalError::PermissionDenied),
                io::ErrorKind::AlreadyExists => Err(InternalError::AlreadyExists),
                io::ErrorKind::IsADirectory => Err(InternalError::PathIsNotAFile),
                io::ErrorKind::ReadOnlyFilesystem => Err(InternalError::ReadOnlyFilesystem),
                io::ErrorKind::FileTooLarge => Err(InternalError::FileTooLarge),
                io::ErrorKind::ResourceBusy => Err(InternalError::ResourceBusy),
                io::ErrorKind::ExecutableFileBusy => Err(InternalError::ExecutableFileBusy),
                _ => Err(InternalError::OsError),
            },
        }
    }

    fn open_read_write(path: &Path) -> InternalResult<File> {
        match File::options()
            .read(true)
            .write(true)
            .create(false)
            .open(path)
        {
            Ok(file) => Ok(file),
            Err(err) => match err.kind() {
                io::ErrorKind::NotFound => Err(InternalError::FileNotFound),
                io::ErrorKind::PermissionDenied => Err(InternalError::PermissionDenied),
                io::ErrorKind::AlreadyExists => Err(InternalError::AlreadyExists),
                io::ErrorKind::IsADirectory => Err(InternalError::PathIsNotAFile),
                io::ErrorKind::ReadOnlyFilesystem => Err(InternalError::ReadOnlyFilesystem),
                io::ErrorKind::FileTooLarge => Err(InternalError::FileTooLarge),
                io::ErrorKind::ResourceBusy => Err(InternalError::ResourceBusy),
                io::ErrorKind::ExecutableFileBusy => Err(InternalError::ExecutableFileBusy),
                _ => Err(InternalError::OsError),
            },
        }
    }

    fn open_create(path: &Path) -> InternalResult<File> {
        match File::options()
            .read(true)
            .write(true)
            .create(true)
            .open(path)
        {
            Ok(file) => Ok(file),
            Err(err) => match err.kind() {
                io::ErrorKind::NotFound => Err(InternalError::FileNotFound),
                io::ErrorKind::PermissionDenied => Err(InternalError::PermissionDenied),
                io::ErrorKind::AlreadyExists => Err(InternalError::AlreadyExists),
                io::ErrorKind::IsADirectory => Err(InternalError::PathIsNotAFile),
                io::ErrorKind::ReadOnlyFilesystem => Err(InternalError::ReadOnlyFilesystem),
                io::ErrorKind::FileTooLarge => Err(InternalError::FileTooLarge),
                io::ErrorKind::ResourceBusy => Err(InternalError::ResourceBusy),
                io::ErrorKind::ExecutableFileBusy => Err(InternalError::ExecutableFileBusy),
                _ => Err(InternalError::OsError),
            },
        }
    }
}

#[cfg(test)]
mod tests {
    use std::{
        env,
        fs::{remove_file, File},
        io::{Read, Write},
        path::{Path, PathBuf},
    };

    use crate::{prelude::InternalError, row::Row};

    use super::{Buffer, Mode};

    pub fn create() -> PathBuf {
        let mut tmp = env::temp_dir();
        tmp.push("test.rs");

        let mut file = File::create(tmp.clone()).expect("failed to create file");

        file.write_all(
            br#"#[derive(Debug)]
struct User {
    name: String,
    age: i32,
}

impl User {
    fn new(name: String, age: i32) -> Self {
        Self {
            name,
            age
        }
    }
}
"#,
        )
        .expect("failed to write");

        tmp
    }

    #[test]
    fn open_file() {
        let path = create();

        let mut buf = Buffer::new();

        buf.open(&path, Mode::ReadWrite)
            .expect("failewd to open file")
            .expect("internal error");

        remove_file(path).expect("failed to remove file");

        assert_eq!(buf.file_name, "test.rs");
        assert_eq!(buf.format, "rs");
        assert_eq!(buf.content.len(), 14);
        assert_eq!(buf.mode, Mode::ReadWrite);
    }

    #[test]
    fn file_not_found() {
        let mut buf = Buffer::new();

        let result = buf
            .open(Path::new("x.rs"), Mode::ReadWrite)
            .expect("failed to open file");
        match result {
            Ok(..) => panic!("must be panic"),
            Err(err) => assert_eq!(err, InternalError::FileNotFound),
        }
    }

    #[test]
    fn get_row() {
        let path = create();

        let mut buf = Buffer::new();

        buf.open(&path, Mode::ReadOnly)
            .expect("failed to open")
            .expect("failed to read");
        remove_file(path).expect("failed to remove file");

        let row = buf.get_row(2);

        assert_eq!(row, Some(Row::from("    name: String,")).as_ref())
    }

    #[test]
    fn remove_file_content() {}

    #[test]
    fn write_to_file() {
        let path = create();

        let mut buf = Buffer::new();

        buf.open(&path, Mode::ReadWrite)
            .expect("failed to open")
            .expect("failed tp read");
        buf.push_row_with_content(r#"fn new_user() {}"#.to_string());

        buf.save().expect("failed to save");

        let mut file = File::open(&path).expect("failed to open file");
        let mut str = String::new();
        file.read_to_string(&mut str).expect("failed to read");
        remove_file(path).expect("failed to delete");

        assert_eq!(str.lines().count(), 15);
    }

    #[test]
    fn edit_single_row_then_write_to_file() {}

    #[test]
    fn add_new_row() {}

    #[test]
    fn get_file_information() {}

    #[test]
    fn change_filename() {}

    #[test]
    fn change_file_prefix() {}

    #[test]
    fn move_file_location() {}
}
