use crossterm::event::MouseEvent;

use crate::{editor::Editor, prelude::InternalResult};

pub trait MouseHandler {
    fn mouse_handler(&mut self, event: MouseEvent) -> InternalResult<()>;
}

impl MouseHandler for Editor {
    fn mouse_handler(&mut self, event: MouseEvent) -> InternalResult<()> {
        todo!()
    }
}
