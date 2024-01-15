use tokio::io::{stdout, AsyncWriteExt};

use crate::{editor::Editor, settings::TITLE_BAR, VERSION};

pub const BAR_ROW_POSITION: u16 = 1;

pub trait FrameDrawer {
    fn draw_bar(&self, col_size: u16);
    fn draw_footer(&self, row_size: u16, col_size: u16);
}

impl FrameDrawer for Editor {
    fn draw_bar(&self, col_size: u16) {
        let mut bar_line = String::from("\x1B[0;0H");

        for _ in 0..col_size {
            bar_line.push('█');
        }

        bar_line.push_str("\x1B[0;2H");
        bar_line.push_str(TITLE_BAR);

        print!("{}", bar_line);
    }

    fn draw_footer(&self, row_size: u16, col_size: u16) {
        let footer_position = row_size - 1;

        // free_goto(footer_position, 0);
        let mut footer_line = String::new();
        for _ in 0..col_size {
            footer_line.push('█');
        }
        print!("{}", footer_line);

        // free_goto(footer_position, 2);
        print!("\x1b[7m{}\x1b[0m", self.buffer.file_name);

        // free_goto(footer_position, 20);
        print!("{}", self.internal_error.to_str());

        // TODO: fix position.
        // free_goto(footer_position, col_size - 18);
        print!(
            "\x1b[7mline: {} column: {}\x1b[0m",
            self.render.cursor.get_row(),
            self.render.cursor.get_col()
        );

        // free_goto(footer_position, col_size - 40);

        print!("\x1b[7m{}\x1b[0m", self.buffer.format);
    }
}
