use super::{frame::FrameDrawer, row::RowRenderer};
use crate::editor::Editor;
use std::thread;

pub trait EditorRenderer: RowRenderer + FrameDrawer {
    fn render_editor(&self, screen: &mut String, col_size: u16, row_size: u16);
}

impl EditorRenderer for Editor {
    fn render_editor(&self, screen: &mut String, col_size: u16, row_size: u16) {
        self.draw_bar(screen, col_size);

        self.render_rows(screen, row_size);

        self.draw_footer(screen, row_size, col_size);
    }
}
