mod editor;
mod frame;
mod prompt;
mod row;

use std::io::{stdout, Write};

use crate::constants::{clear, cursors};
use crate::editor::{Editor, Layouts};
use crate::prelude::*;
use crate::size::Cursor as _;

pub use self::frame::BAR_ROW_POSITION;

use self::{editor::EditorRenderer, prompt::PromptRenderer};

pub trait Update: EditorRenderer + PromptRenderer {
    fn update(&self) -> IoResult<()>;
}

impl Update for Editor {
    fn update(&self) -> IoResult<()> {
        let (terminal_row_size, terminal_col_size) = self.terminal_size.get_row_col();

        let mut screen = String::from(clear::UPDATE_INITIALIZER);

        match self.layout {
            Layouts::Editor => {
                self.render_editor(&mut screen, terminal_col_size, terminal_row_size)
            }
            Layouts::Prompt => self.render_prompt(terminal_row_size),
        };

        screen.push_str(&self.render.cursor.restore());

        let mut stdout = stdout().lock();
        stdout.write_all(screen.as_bytes());
        stdout.flush()?;
        Ok(())
    }
}
