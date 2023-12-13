use crate::{cursor::Cursor, range::Range, update::BAR_ROW_POSITION};

pub const EDITOR_FIRST_ROW_POSITION: u16 = BAR_ROW_POSITION + 1;

pub trait ArrowMoves {
    fn move_right(&mut self);
    fn move_left(&mut self);
    fn move_up(&mut self);
    fn move_down(&mut self);
}

#[derive(Debug)]
/// store data we need it many and many times.
pub struct Render {
    pub cursor: Cursor,
    /// this range provide first row and last row to display
    /// end of range can increase or decreased
    end_editor_position: u16,
    /// range position of buffer
    position: Range<usize>,
    /// current buffer position
    pub row_position: usize,
    // store perv/current/next row length
    pub perv_row_len: usize,
    pub current_row_len: usize,
    pub next_row_len: usize,
    // current buffer len
    buffer_len: usize,
}

impl Render {
    pub fn new() -> Self {
        Self {
            cursor: Cursor::new(),
            end_editor_position: 0,
            position: Range::new(0, 0),
            row_position: 0,
            buffer_len: 0,
            perv_row_len: 0,
            current_row_len: 0,
            next_row_len: 0,
        }
    }

    /// this function called per down and up movement of cursor
    pub fn update_buffer_info(
        &mut self,
        buffer_len: usize,
        perv_row_len: usize,
        current_row_len: usize,
        next_row_len: usize,
    ) {
        self.buffer_len = buffer_len;
        self.perv_row_len = perv_row_len;
        self.current_row_len = current_row_len;
        self.next_row_len = next_row_len;
    }

    /// this function called when buffer changed
    pub fn update(&mut self, buffer_len: usize) {
        let end_position = if buffer_len > self.end_editor_position as usize {
            self.end_editor_position as usize
        } else {
            buffer_len
        };

        self.cursor = Cursor::new();
        self.position = Range::new(
            0,
            end_position, // TODO FIX
        );
        self.row_position = 0;
        self.buffer_len = buffer_len;
    }

    pub fn increase_position(&mut self) {
        if self.buffer_len == 0 || self.position.end == self.buffer_len {
            return;
        }

        self.position.start += 1;
        self.position.end += 1;
    }

    pub fn decrease_position(&mut self) {
        if self.buffer_len == 0 || self.position.start == 0 {
            return;
        }

        self.position.start -= 1;
        self.position.end -= 1;
    }

    pub fn set_end_editor_position(&mut self, end_row: u16) {
        self.end_editor_position = end_row - 2;
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
    fn move_right(&mut self) {
        if (self.cursor.col as usize) == self.current_row_len {
            return;
        }
        self.cursor.col += 1;
    }

    fn move_left(&mut self) {}

    fn move_up(&mut self) {
        if self.cursor.row == 2 {
            self.decrease_position();
            return;
        }

        if self.row_position != 0 {
            self.row_position -= 1;
        }

        self.cursor.row -= 1;
    }

    fn move_down(&mut self) {
        if ((self.cursor.row + 1) as usize) > self.buffer_len {
            return;
        }

        if self.cursor.row == self.end_editor_position {
            self.increase_position();
            return;
        }

        if self.row_position != self.buffer_len {
            self.row_position += 1;
        }

        self.cursor.row += 1
    }
}
