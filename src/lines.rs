use std::{
    fs::File,
    io::{BufRead, BufReader},
    ops::{self, Deref, DerefMut},
};

use crate::{prelude::*, row::Row};

#[derive(Debug, Clone)]
pub struct Lines {
    pub inner: Vec<Row>,
}

impl Lines {
    pub fn new() -> Self {
        Self {
            inner: vec![Row::new()],
        }
    }

    #[inline]
    pub fn len(&self) -> usize {
        self.inner.len()
    }

    #[inline]
    pub fn push_empty_row(&mut self) {
        self.inner.push(Row::new())
    }

    #[inline]
    pub fn push_row_with_content(&mut self, content: String) {
        self.inner.push(Row::from(content))
    }

    #[inline]
    pub fn read(file: &mut File) -> IoResult<Self> {
        BufReader::new(file).lines().try_collect::<Lines>()
    }
}

impl ToString for Lines {
    fn to_string(&self) -> String {
        let mut str = String::new();
        for line in &self.inner {
            str.push_str(line);
        }
        str
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

#[cfg(test)]
mod tests {
    use std::{
        env,
        fs::{remove_file, File},
        io::Write,
        path::PathBuf,
    };

    use crate::lines::Lines;

    fn create() -> PathBuf {
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
    fn file_to_line() {
        let path = create();

        let mut file = File::open(path.clone()).unwrap();

        assert_eq!(Lines::read(&mut file).unwrap().len(), 14);
        remove_file(path);
    }
}
