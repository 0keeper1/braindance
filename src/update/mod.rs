mod editor;
mod frame;
// mod menu;
mod prompt;
mod row;

use std::io::{stdout, Write};

use crate::prelude::*;
use crate::{
    editor::{Editor, Layouts},
    utils::{clean_screen, hide_cursor},
};

pub use self::frame::BAR_ROW_POSITION;
use self::{editor::EditorRenderer, prompt::PromptRenderer};

pub trait Update: EditorRenderer + PromptRenderer {
    fn update(&self) -> IoResult<()>;
}

impl Update for Editor {
    fn update(&self) -> IoResult<()> {
        let (terminal_col_size, terminal_row_size) = self.terminal.get_terminal_size();

        hide_cursor();
        clean_screen();

        match self.layout {
            Layouts::Editor => self.render_editor(terminal_col_size, terminal_row_size),
            Layouts::Prompt => self.render_prompt(terminal_row_size),
        };

        self.render.cursor.restore();
        stdout().flush()?;
        Ok(())
    }
}
