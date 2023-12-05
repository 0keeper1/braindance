use crate::{constants::cursors, render::EDITOR_FIRST_ROW_POSITION};

#[derive(Debug)]
pub struct Cursor {
    pub col: u16,
    pub row: u16,
}

impl Cursor {
    pub const fn new() -> Self {
        Self {
            col: 1,
            row: EDITOR_FIRST_ROW_POSITION,
        }
    }

    #[inline]
    /// to can be Row length so we add one
    pub fn move_col_to(&mut self, to: u16) {
        self.col = to + 1;
    }

    #[inline]
    pub fn move_row_to(&mut self, to: u16) {
        self.row = to;
    }

    pub fn goto(&mut self, row: u16, col: u16) {
        self.col = col;
        self.row = row;
    }

    #[inline]
    pub fn free_row_move(&self, row: u16) {
        print!("\x1B[{};{}H", row, self.col)
    }

    #[inline]
    pub fn free_column_move(&self, col: u16) {
        print!("\x1B[{};{}H", self.row, col);
    }

    pub fn restore(&self) {
        print!("\x1B[{};{}H", self.row, self.col);
        self.show();
    }

    #[inline]
    pub fn hide() {
        print!("{}", cursors::CURSOR_HIDE)
    }

    #[inline]
    pub fn show(&self) {
        print!("{}", cursors::CURSOR_SHOW)
    }
}

#[inline]
pub fn free_goto(row: u16, col: u16) {
    print!("\x1B[{};{}H", row, col);
}
