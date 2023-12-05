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
                info!("before move right event {:?}", self.render);
                self.render.move_right();
                info!("after move right event {:?}", self.render);

                Ok(())
            }
            KeyEvent {
                code: KeyCode::Left,
                modifiers: KeyModifiers::NONE,
                ..
            } => {
                info!("before move left event {:?}", self.render);
                self.render.move_left();
                info!("after move left event {:?}", self.render);

                Ok(())
            }
            KeyEvent {
                code: KeyCode::Up,
                modifiers: KeyModifiers::NONE,
                ..
            } => {
                info!("before move up event {:?}", self.render);
                self.render.move_up();
                info!("after move up event {:?}", self.render);
                Ok(())
            }
            KeyEvent {
                code: KeyCode::Down,
                modifiers: KeyModifiers::NONE,
                ..
            } => {
                info!("before move down event {:?}", self.render);
                self.render.move_down();
                info!("after move down event {:?}", self.render);

                Ok(())
            }
            _ => Err(InternalError::NoError),
        }
    }
}
