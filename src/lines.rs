use std::ops::{self, Deref, DerefMut};
use std::{fs::File, io::Read};

use crate::error::Result;
use crate::prelude::IoResult;
use crate::row::Row;
use crate::utils::ReadLines;

#[derive(Debug)]
pub struct Lines {
    pub inner: Vec<Row>,
}

impl Lines {
    pub fn new() -> Self {
        Self { inner: Vec::new() }
    }

    #[inline]
    pub fn len(&self) -> usize {
        self.inner.len()
    }

    pub fn read_file(file: &mut File) -> IoResult<Self> {
        let mut buf = Vec::new();
        file.read_to_end(&mut buf)?;
        Ok(buf.lines())
    }

    pub fn export(&self) -> Vec<u8> {
        let mut vec: Vec<u8> = Vec::new();
        for row in &self.inner {
            for char in row.export() {
                vec.push(*char)
            }
        }
        vec
    }
}

impl Deref for Lines {
    type Target = Vec<Row>;

    fn deref(&self) -> &Self::Target {
        &self.inner
    }
}

impl DerefMut for Lines {
    fn deref_mut(&mut self) -> &mut Self::Target {
        &mut self.inner
    }
}

impl ops::IndexMut<ops::RangeFull> for Lines {
    fn index_mut(&mut self, index: ops::RangeFull) -> &mut Self::Output {
        &mut self.inner[index]
    }
}

impl ops::Index<ops::RangeFull> for Lines {
    type Output = [Row];

    fn index(&self, index: ops::RangeFull) -> &Self::Output {
        &self.inner[index]
    }
}

impl IntoIterator for Lines {
    type Item = Row;

    type IntoIter = std::vec::IntoIter<Self::Item>;

    fn into_iter(self) -> Self::IntoIter {
        self.inner.into_iter()
    }
}
