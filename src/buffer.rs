use std::{fs::File, io, path::PathBuf};

use crate::{error::Result, history::History, lines::Lines, prelude::IoResult, row::Row};

pub trait FileFunctionalities {
    fn save(&mut self) -> io::Result<()>;
    fn open(&self) -> io::Result<File>;
    fn read(&mut self) -> io::Result<()>;
}

trait LinesModifier {
    fn write_to_row(&mut self, row: usize) -> Result<()>;
}

#[derive(Debug)]
/// store File data and more information
pub struct Buffer {
    path: PathBuf,
    pub format: String,
    pub file_name: String,
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
        }
    }

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

    /// return (buffer_len, perv_row_len, current_row_len, next_row_len)
    pub fn set_path_and_read(&mut self, path: PathBuf) -> IoResult<(usize, usize, usize, usize)> {
        self.path = path;
        self.read()?;
        let buffer_len = self.content.len();

        let first_row_len = match self.content.first() {
            Some(row) => row.len(),
            None => 0,
        };

        let second_row_len = match self.get_row(1) {
            Some(row) => row.len(),
            None => 0,
        };
        Ok((buffer_len, 0, first_row_len, second_row_len))
    }

    pub fn read_file(&mut self) -> IoResult<()> {
        self.read()
    }

    pub fn len(&self) -> usize {
        self.content.len()
    }
}

impl FileFunctionalities for Buffer {
    fn save(&mut self) -> io::Result<()> {
        todo!()
    }

    fn open(&self) -> io::Result<File> {
        File::options()
            .read(true)
            .write(true)
            .create(true)
            .open(&self.path)
    }

    fn read(&mut self) -> io::Result<()> {
        let mut file = self.open()?;
        self.content = Lines::read_file(&mut file)?;
        Ok(())
    }
}
