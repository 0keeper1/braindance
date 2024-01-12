use crate::{cursor::free_goto, editor::Editor, VERSION};

pub const BAR_ROW_POSITION: u16 = 1;

pub trait FrameDrawer {
    async fn draw_bar(&self, col_size: u16);
    async fn draw_footer(&self, row_size: u16, col_size: u16);
}

impl FrameDrawer for Editor {
    async fn draw_bar(&self, col_size: u16) {
        free_goto(0, 0);

        for _ in 0..col_size {
            print!("█");
        }

        free_goto(0, 2);
        print!("\x1b[7mBRAINDANCE {}\x1b[0m", VERSION);
    }

    async fn draw_footer(&self, row_size: u16, col_size: u16) {
        let footer_position = row_size - 1;

        free_goto(footer_position, 0);
        for _ in 0..col_size {
            print!("█")
        }

        free_goto(footer_position, 2);
        print!("\x1b[7m{}\x1b[0m", self.buffer.file_name);

        free_goto(footer_position, 20);
        print!("{}", self.internal_error.to_str());

        // TODO: fix position.
        free_goto(footer_position, col_size - 18);
        print!(
            "\x1b[7mline: {} column: {}\x1b[0m",
            self.render.cursor.row, self.render.cursor.col
        );

        free_goto(footer_position, col_size - 40);

        print!("\x1b[7m{}\x1b[0m", self.buffer.format);
    }
}
