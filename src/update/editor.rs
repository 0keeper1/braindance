use crate::editor::Editor;
use std::thread;
use super::{frame::FrameDrawer, row::RowRenderer};

pub trait EditorRenderer: RowRenderer + FrameDrawer {
    async fn render_editor(&self, col_size: u16, row_size: u16);
}

impl EditorRenderer for Editor {
    async fn render_editor(&self, col_size: u16, row_size: u16) {

        self.draw_bar(col_size).await;

        self.draw_footer(row_size, col_size).await;
        // self.render_rows(row_size);
    }
}
