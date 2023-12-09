use crate::prelude::*;

use crossterm::terminal::{disable_raw_mode, enable_raw_mode, size as terminal_size};

const MINIMUM_ROW_SIZE: u16 = 10;
const MINIMUM_COL_SIZE: u16 = 10;

#[derive(Debug, Clone, Copy)]
pub struct Size {
    pub col: u16,
    pub row: u16,
}

#[derive(Debug)]
pub struct Terminal {
    size: Size,
    is_raw_mode: bool,
}

impl Terminal {
    pub fn new() -> Self {
        Self {
            size: Size::new(0, 0),
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

    pub fn initialize_size(&mut self) -> Result<()> {
        let (col, row) = terminal_size()?;
        Ok(self.update_size(col, row))
    }

    #[inline]
    pub fn is_raw_mode(&self) -> bool {
        self.is_raw_mode
    }

    #[inline]
    pub fn get_col_size(&self) -> u16 {
        self.size.col
    }

    #[inline]
    pub fn get_row_size(&self) -> u16 {
        self.size.row
    }

    /// return size of the terminal (col, row)
    pub fn get_terminal_size(&self) -> (u16, u16) {
        (self.size.col, self.size.row)
    }

    #[inline]
    pub fn get_size(&self) -> &Size {
        &self.size
    }

    pub fn update_size(&mut self, col: u16, row: u16) -> InternalResult<()> {
        if col < MINIMUM_COL_SIZE || row < MINIMUM_ROW_SIZE {
            Err(InternalError::MinimumTerminalSizeReached)
        } else {
            self.size.update_size(col, row);
            Ok(())
        }
    }

    #[inline]
    pub fn get_mut_size(&mut self) -> &mut Size {
        &mut self.size
    }
}

impl Size {
    pub fn new(col: u16, row: u16) -> Self {
        Self { col, row }
    }

    pub fn update_size(&mut self, col: u16, row: u16) {
        self.col = col;
        self.row = row;
    }
}

#[cfg(test)]
mod tests {
    use crossterm::terminal::is_raw_mode_enabled;

    use crate::prelude::InternalError;

    use super::{Terminal, MINIMUM_COL_SIZE, MINIMUM_ROW_SIZE};

    #[test]
    fn enable_raw_mode() {
        let mut terminal = Terminal::new();
        terminal.enable_raw_mode();

        assert!(terminal.is_raw_mode());
        assert!(is_raw_mode_enabled().unwrap())
    }

    #[test]
    fn disable_raw_mode() {
        let mut terminal = Terminal::new();
        terminal.enable_raw_mode();
        terminal.disable_raw_mode();

        assert_eq!(terminal.is_raw_mode(), is_raw_mode_enabled().unwrap());
    }

    #[test]
    fn reach_minimum_terminal_size() {
        let mut terminal = Terminal::new();

        let result = terminal.update_size(MINIMUM_COL_SIZE - 2, MINIMUM_ROW_SIZE - 2);
        match result {
            Ok(..) => panic!("must be panic"),
            Err(err) => assert_eq!(err, InternalError::MinimumTerminalSizeReached),
        }
    }
}
