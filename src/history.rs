use crate::row::Row;

#[derive(Debug)]
pub struct History {
    inner: Vec<Row>,
}

impl History {
    pub fn new() -> Self {
        Self { inner: Vec::new() }
    }
}
