use log::info;

use crate::{cursor::Cursor, range::Range, update::BAR_ROW_POSITION};

pub const EDITOR_FIRST_ROW_POSITION: u16 = BAR_ROW_POSITION + 1;

pub trait ArrowMoves {
    fn move_right(&mut self, terminal_col_size: u16, current_row_len: u16);
    fn move_left(&mut self, perv_row_len: u16);
    fn move_up(&mut self);
    fn move_down(&mut self);
}

#[derive(Debug)]
pub struct Render {
    pub cursor: Cursor,
    /// this range provide first row and last row to display
    /// end of range can increase or decreased
    end_editor_position: u16,
    /// range position of buffer
    position: Range<usize>,
    /// current buffer position
    pub row_position: usize,
    // current buffer len
    current_buffer_len: usize,
}

impl Render {
    pub fn new() -> Self {
        Self {
            cursor: Cursor::new(),
            end_editor_position: 0,
            position: Range::new(0, 0),
            row_position: 0,
            current_buffer_len: 0,
        }
    }

    /// this function called when buffer changed
    pub fn update(&mut self, current_buffer_len: usize) {
        let end_position = if current_buffer_len > self.end_editor_position as usize {
            self.end_editor_position as usize
        } else {
            current_buffer_len
        };

        self.cursor = Cursor::new();
        self.position = Range::new(
            0,
            end_position, // TODO FIX
        );
        self.row_position = 0;
        self.current_buffer_len = current_buffer_len;
    }

    pub fn increase_position(&mut self) {
        if self.position.end + 1 > self.current_buffer_len {
            return;
        }
        self.position.start += 1;
        self.position.end += 1;
    }

    #[allow(clippy::absurd_extreme_comparisons)]
    pub fn decrease_position(&mut self) {
        info!("{self:?}");
        if self.position.start - 1 == 0 {
            self.position.start = 0;
            return;
        };
        self.position.start -= 1;
        self.position.end -= 1;
    }

    pub fn set_end_editor_position(&mut self, end_row: u16) {
        self.end_editor_position = end_row;
    }

    #[inline]
    pub fn get_end_editor_position(&self) -> u16 {
        self.end_editor_position
    }

    #[inline]
    pub fn get_position(&self) -> &Range<usize> {
        &self.position
    }
}

impl ArrowMoves for Render {
    fn move_right(&mut self, terminal_col_size: u16, mut current_row_len: u16) {
        current_row_len += 1;

        if self.cursor.col + 1 > terminal_col_size || self.cursor.col + 1 > current_row_len {
            return;
        }

        if current_row_len == 0 {
            // self.move_down(terminal_row_size, buffer_len)
        }

        if self.cursor.col + 1 >= current_row_len || current_row_len == 0 {
            self.cursor.col = 0;
            self.cursor.row += 1;
            self.row_position += 1;
        }

        self.cursor.col += 1;
    }

    fn move_left(&mut self, perv_row_len: u16) {
        if self.cursor.col - 1 == 0 {
            self.move_up();
            self.cursor.col = perv_row_len + 1;
            return;
        }
        self.cursor.col -= 1;
    }

    fn move_up(&mut self) {
        self.decrease_position(); // TODO FIX PANIC

        if self.cursor.row - 1 < EDITOR_FIRST_ROW_POSITION {
            return;
        }

        if self.row_position - 1 != 1 {
            self.row_position -= 1;
        }

        self.cursor.row -= 1;
    }

    fn move_down(&mut self) {
        self.increase_position();

        if self.cursor.row + 1 > self.end_editor_position {
            return;
        }

        if self.row_position + 1 != self.current_buffer_len {
            self.row_position += 1;
        }

        self.cursor.row += 1;
    }
}
