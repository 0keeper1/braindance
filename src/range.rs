#[derive(Debug, Clone, Copy)]
pub struct Range<T> {
    pub start: T,
    pub end: T,
}

impl<T> Range<T> {
    pub fn new(start: T, end: T) -> Self {
        Self { start, end }
    }

    #[inline]
    pub fn increase_end(&mut self, end: T) {
        self.end = end;
    }

    pub fn set_range(&mut self, start: T, end: T) {
        self.start = start;
        self.end = end;
    }

    #[inline]
    pub fn set_end(&mut self, end: T) {
        self.end = end
    }

    #[inline]
    pub fn increase_start(&mut self, start: T) {
        self.start = start;
    }
}

impl Range<usize> {
    pub fn increase_both(&mut self) {
        self.start += 1;
        self.end += 1;
    }
}

impl Range<i32> {
    pub fn increase_both(&mut self) {
        self.start += 1;
        self.end += 1;
    }
}
