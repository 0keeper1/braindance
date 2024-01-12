use crate::prelude::*;

use crossterm::terminal::{disable_raw_mode, enable_raw_mode, size as terminal_size};

const MINIMUM_ROW_SIZE: u16 = 10;
const MINIMUM_COL_SIZE: u16 = 10;

#[derive(Debug)]
pub struct Terminal {
    col: u16,
    row: u16,
    is_raw_mode: bool,
}

impl Terminal {
    pub fn new() -> Self {
        Self {
            col: 0,
            row: 0,
            is_raw_mode: false,
        }
    }

    pub fn enable_raw_mode(&mut self) -> IoResult<()> {
        enable_raw_mode()?;
        self.is_raw_mode = true;
        Ok(())
    }

    pub fn disable_raw_mode(&mut self) -> IoResult<()> {
        disable_raw_mode()?;
        self.is_raw_mode = false;
        Ok(())
    }

    #[inline]
    pub fn is_raw_mode(&self) -> bool {
        self.is_raw_mode
    }

    #[inline]
    pub fn get_col_size(&self) -> u16 {
        self.col
    }

    #[inline]
    pub fn get_row_size(&self) -> u16 {
        self.row
    }

    /// return size of the terminal (col, row)
    pub fn get_terminal_size(&self) -> (u16, u16) {
        (self.col, self.row)
    }

    pub fn update_size(&mut self) -> AppResult<()> {
        let (col, row) = terminal_size()?;
        if col < MINIMUM_COL_SIZE || row < MINIMUM_ROW_SIZE {
            Ok(Err(InternalError::MinimumTerminalSizeReached))
        } else {
            self.col = col;
            self.row = row;
            Ok(Ok(()))
        }
    }
}

#[cfg(test)]
mod tests {
    use crossterm::terminal::is_raw_mode_enabled;

    use crate::prelude::InternalError;

    use super::Terminal;

    #[test]
    #[ignore = "not working on github workflow"]
    fn enable_raw_mode() {
        let mut terminal = Terminal::new();
        terminal.enable_raw_mode().unwrap();

        assert_eq!(terminal.is_raw_mode(), is_raw_mode_enabled().unwrap());

        crossterm::terminal::disable_raw_mode().unwrap();
    }

    #[test]
    #[ignore = "not working on github workflow"]
    fn disable_raw_mode() {
        let mut terminal = Terminal::new();
        terminal.enable_raw_mode().unwrap();
        terminal.disable_raw_mode().unwrap();

        assert_eq!(terminal.is_raw_mode(), is_raw_mode_enabled().unwrap());
    }

    #[test]
    #[ignore = "not working on github workflow"]
    fn reach_minimum_terminal_size() {
        let mut terminal = Terminal::new();

        let result = terminal.update_size().expect("IO error");
        match result {
            Ok(..) => panic!("must be panic"),
            Err(err) => assert_eq!(err, InternalError::MinimumTerminalSizeReached),
        }
    }
}
