use std::{
    fmt,
    ops::{Deref, DerefMut},
    str,
};

use crate::lines::Lines;

#[derive(Debug, PartialEq, Eq, Clone)]
pub struct Row {
    pub inner: Vec<u8>,
}

impl Row {
    pub fn new() -> Self {
        Self { inner: Vec::new() }
    }

    #[inline]
    fn set_inner(vec: Vec<u8>) -> Self {
        Self { inner: vec }
    }

    #[inline]
    pub fn export(&self) -> &Vec<u8> {
        &self.inner
    }
}

impl fmt::Display for Row {
    #[inline]
    fn fmt(&self, f: &mut fmt::Formatter<'_>) -> fmt::Result {
        fmt::Display::fmt(&**self, f)
    }
}

impl From<&[u8]> for Row {
    #[inline]
    fn from(value: &[u8]) -> Self {
        Row::set_inner(Vec::from(value))
    }
}

impl From<&str> for Row {
    fn from(value: &str) -> Self {
        Self {
            inner: value.into(),
        }
    }
}

impl From<Vec<u8>> for Row {
    #[inline]
    fn from(value: Vec<u8>) -> Self {
        Row::set_inner(value)
    }
}

impl From<String> for Row {
    #[inline]
    fn from(value: String) -> Self {
        Row::from(value.as_bytes())
    }
}

impl FromIterator<String> for Lines {
    fn from_iter<T: IntoIterator<Item = String>>(iter: T) -> Self {
        let mut vec = Vec::new();
        for line in iter {
            vec.push(Row::from(line))
        }
        Lines { inner: vec }
    }
}

impl Deref for Row {
    type Target = str;

    fn deref(&self) -> &Self::Target {
        unsafe { str::from_utf8_unchecked(&self.inner) }
    }
}

impl DerefMut for Row {
    #[inline]
    fn deref_mut(&mut self) -> &mut str {
        unsafe { str::from_utf8_unchecked_mut(&mut self.inner) }
    }
}

impl IntoIterator for Row {
    type Item = u8;

    type IntoIter = std::vec::IntoIter<Self::Item>;

    fn into_iter(self) -> Self::IntoIter {
        self.inner.into_iter()
    }
}
