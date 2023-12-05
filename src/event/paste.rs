use crate::{editor::Editor, prelude::InternalResult};

pub trait PasteHandler {
    fn paste_handler(&mut self, text: &str) -> InternalResult<()>;
}

impl PasteHandler for Editor {
    fn paste_handler(&mut self, text: &str) -> InternalResult<()> {
        todo!()
    }
}
