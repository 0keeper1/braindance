use crossterm::terminal::{disable_raw_mode, enable_raw_mode, size as terminal_size};

use crate::prelude::*;

pub trait TerminalSize {
    const MINIMUM_ROW_SIZE: u16 = 10;
    const MINIMUM_COL_SIZE: u16 = 10;

    fn update_size(&mut self) -> AppResult<()>;
}

pub trait Cursor {
    const FIRST_ROW: u16 = 1;

    fn new() -> Self;

    fn increase_col(&mut self);

    fn increase_row(&mut self);

    fn decrease_col(&mut self);

    fn decrease_row(&mut self);

    fn restore(&self) -> String;

    fn free_goto(row: u16, col: u16) -> String;
}

#[derive(Debug, Default)]
pub struct RowCol {
    row: u16,
    col: u16,
}

impl RowCol {
    pub fn new(row: u16, col: u16) -> Self {
        Self { row, col }
    }

    /// return (row, col)
    pub fn get_row_col(&self) -> (u16, u16) {
        (self.row, self.col)
    }

    #[inline]
    pub fn get_row(&self) -> u16 {
        self.row
    }

    #[inline]
    pub fn get_col(&self) -> u16 {
        self.col
    }

    #[inline]
    fn set_row(&mut self, row: u16) {
        self.row = row;
    }

    #[inline]
    fn set_col(&mut self, col: u16) {
        self.col = col;
    }

    #[inline]
    pub fn set_row_col(&mut self, row: u16, col: u16) {
        self.row = row;
        self.col = col;
    }
}

impl Cursor for RowCol {
    fn new() -> Self {
        Self {
            row: Self::FIRST_ROW,
            col: 0,
        }
    }

    #[inline]
    fn increase_col(&mut self) {
        self.col += 1;
    }

    #[inline]
    fn increase_row(&mut self) {
        self.row += 1;
    }

    #[inline]
    fn decrease_col(&mut self) {
        self.col -= 1;
    }

    #[inline]
    fn decrease_row(&mut self) {
        self.row -= 1;
    }

    fn restore(&self) -> String {
        format!("\x1B[{};{}H", self.row, self.col)
    }

    fn free_goto(row: u16, col: u16) -> String {
        format!("\x1B[{};{}H", row, col)
    }
}

impl TerminalSize for RowCol {
    fn update_size(&mut self) -> AppResult<()> {
        let (col, row) = terminal_size()?;
        if col < Self::MINIMUM_COL_SIZE || row < Self::MINIMUM_ROW_SIZE {
            Ok(Err(InternalError::MinimumTerminalSizeReached))
        } else {
            self.col = col;
            self.row = row;
            Ok(Ok(()))
        }
    }
}
