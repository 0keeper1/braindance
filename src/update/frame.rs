use tokio::io::{stdout, AsyncWriteExt};

use crate::{
    editor::Editor,
    settings::TITLE_BAR,
    size::{self, Cursor, RowCol},
    VERSION,
};

pub const BAR_ROW_POSITION: u16 = 1;

pub trait FrameDrawer {
    fn draw_bar(&self, screen: &mut String, col_size: u16);
    fn draw_footer(&self, screen: &mut String, row_size: u16, col_size: u16);
}

impl FrameDrawer for Editor {
    fn draw_bar(&self, screen: &mut String, col_size: u16) {
        screen.push_str("\x1B[0;0H");

        for _ in 0..col_size {
            screen.push('█');
        }

        screen.push_str("\x1B[0;2H");
        screen.push_str(TITLE_BAR);
    }

    fn draw_footer(&self, screen: &mut String, row_size: u16, col_size: u16) {
        let footer_position = self.render.footer_row;

        screen.push_str(&RowCol::free_goto(footer_position, 0));

        for _ in 0..col_size {
            screen.push('█');
        }

        screen.push_str(&RowCol::free_goto(footer_position, 2));
        screen.push_str(&format!("\x1b[7m{}\x1b[0m", self.buffer.file_name));

        screen.push_str(&RowCol::free_goto(footer_position, 20));
        screen.push_str(self.internal_error.to_str());

        // TODO: fix position.
        screen.push_str(&RowCol::free_goto(footer_position, col_size - (col_size / 3)));
        screen.push_str(&format!(
            "\x1b[7mline: {} column: {}\x1b[0m",
            self.render.cursor.get_row(),
            self.render.cursor.get_col()
        ));
    }
}
