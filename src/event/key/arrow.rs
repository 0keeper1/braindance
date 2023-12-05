use crossterm::event::{KeyCode, KeyEvent, KeyModifiers};
use log::info;

use crate::{
    editor::Editor,
    prelude::{InternalError, InternalResult},
    render::ArrowMoves,
};

pub trait ArrowHandler {
    fn arrow(&mut self, event: &KeyEvent) -> InternalResult<()>;
}

impl ArrowHandler for Editor {
    fn arrow(&mut self, event: &KeyEvent) -> InternalResult<()> {
        match event {
            KeyEvent {
                code: KeyCode::Right,
                modifiers: KeyModifiers::NONE,
                ..
            } => {
                let terminal_col_size = self.terminal.get_col_size();
                let row_len = self.buffer.get_row_len(self.render.row_position);
                self.render.move_right(terminal_col_size, row_len as u16);

                Ok(())
            }
            KeyEvent {
                code: KeyCode::Left,
                modifiers: KeyModifiers::NONE,
                ..
            } => {
                let perv_row_len = self.buffer.get_row_len(self.render.row_position - 1) as u16;
                self.render.move_left(perv_row_len);
                Ok(())
            }
            KeyEvent {
                code: KeyCode::Up,
                modifiers: KeyModifiers::NONE,
                ..
            } => {
                self.render.move_up();
                Ok(())
            }
            KeyEvent {
                code: KeyCode::Down,
                modifiers: KeyModifiers::NONE,
                ..
            } => {
                self.render.move_down();
                Ok(())
            }
            _ => Err(InternalError::NoError),
        }
    }
}
