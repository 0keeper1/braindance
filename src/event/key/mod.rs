mod arrow;
mod char;
mod shortcut;

use crossterm::event::{KeyCode, KeyEvent, KeyModifiers};
use log::{info, trace, warn};

use crate::{
    editor::Editor,
    prelude::{InternalError, InternalResult},
};

use self::arrow::ArrowHandler;

pub trait KeyHandler: ArrowHandler {
    fn key_handler(&mut self, event: KeyEvent) -> InternalResult<()>;
}

impl KeyHandler for Editor {
    fn key_handler(&mut self, event: KeyEvent) -> InternalResult<()> {
        match event {
            ref event @ KeyEvent {
                code: KeyCode::Down | KeyCode::Up | KeyCode::Right | KeyCode::Left,
                ..
            } => self.arrow(event),
            KeyEvent {
                code,
                modifiers: KeyModifiers::ALT | KeyModifiers::CONTROL,
                ..
            } => Ok(()),
            ref event @ KeyEvent {
                code,
                modifiers: KeyModifiers::NONE | KeyModifiers::SHIFT,
                ..
            } => {
                Ok(())
            }
            _ => {
                self.exit = true;
                Err(InternalError::KeyDoesNotSupported)
            }
        }
    }
}
