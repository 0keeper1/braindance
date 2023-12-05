mod key;
mod mouse;
mod paste;

use std::time::Duration;

use crossterm::event::{poll, read, Event};
use log::info;

use crate::{editor::Editor, prelude::*, row, settings::MAXIMUM_KEY_DURATION_TIME};

use self::{key::KeyHandler, mouse::MouseHandler, paste::PasteHandler};

pub trait EventHandler: PasteHandler + MouseHandler + KeyHandler {
    fn event(&mut self) -> IoResult<()>;
}

impl EventHandler for Editor {
    fn event(&mut self) -> IoResult<()> {
        if poll(Duration::from_millis(1500))? {
            let ret = match read()? {
                Event::Resize(col, row) => {
                    self.render.set_end_editor_position(row - 2);
                    self.terminal.update_size(col, row)
                }
                Event::FocusGained => {
                    println!("GAIN");
                    Ok(())
                }
                Event::FocusLost => {
                    println!("LOST");
                    Ok(())
                }
                Event::Key(key) => self.key_handler(key),
                Event::Mouse(mouse) => self.mouse_handler(mouse),
                Event::Paste(text) => self.paste_handler(&text),
            };
            match ret {
                Ok(..) => self.set_no_error(),
                Err(error) => self.set_error(error),
            }
        } else {
            info!("Timeout")
        }
        Ok(())
    }
}
