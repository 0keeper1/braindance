use crossterm::terminal::{disable_raw_mode, enable_raw_mode, size as terminal_size};

use crate::prelude::*;


pub trait TerminalSize {
    const MINIMUM_ROW_SIZE: u16 = 10;
    const MINIMUM_COL_SIZE: u16 = 10;

    fn update_size(&mut self) -> AppResult<()>;
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
    pub fn get_sizes(&self) -> (u16, u16) {
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

    pub fn set_sizes(&mut self, row: u16, col: u16) {
        self.row = row;
        self.col = col;
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