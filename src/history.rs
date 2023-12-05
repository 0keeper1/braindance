#[derive(Debug)]
pub struct History {
    inner: Vec<u8>,
}

impl History {
    pub fn new() -> Self {
        Self { inner: Vec::new() }
    }
}
