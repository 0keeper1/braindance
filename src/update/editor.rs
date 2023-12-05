use crate::{editor::Editor, utils::clean_screen};

use super::{frame::FrameDrawer, row::RowRenderer};

pub trait EditorRenderer: RowRenderer + FrameDrawer {
    fn render_editor(&self, col_size: u16, row_size: u16);
}

impl EditorRenderer for Editor {
    fn render_editor(&self, col_size: u16, row_size: u16) {
        clean_screen();

        self.draw_bar(col_size);

        self.render_rows(row_size);

        self.draw_footer(row_size, col_size);
    }
}
