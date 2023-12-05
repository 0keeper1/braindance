use std::{
    fmt::Display,
    ops::{Deref, DerefMut},
    str,
};

use crate::error::Result;

/// store prompt command and execute the command
#[derive(Debug)]
pub struct Prompt {
    pub command: Vec<u8>,
    input: Vec<u8>,
}

impl Prompt {
    pub fn new() -> Self {
        Self {
            command: Vec::new(),
            input: Vec::new(),
        }
    }

    pub fn push_to_command(&mut self, char: u8) {
        self.command.push(char)
    }

    pub fn push_to_input(&mut self, char: u8) {
        self.input.push(char)
    }

    pub fn pop_from_command(&mut self) {
        self.command.pop();
    }

    pub fn pop_from_input(&mut self) {
        self.input.pop();
    }

    pub fn clear_command(&mut self) {
        self.command.clear()
    }

    pub fn clear_input(&mut self) {
        self.input.clear()
    }

    pub fn exec(&mut self) {}
}

impl Deref for Prompt {
    type Target = str;

    fn deref(&self) -> &Self::Target {
        unsafe { str::from_utf8_unchecked(&self.command) }
    }
}

impl DerefMut for Prompt {
    #[inline]
    fn deref_mut(&mut self) -> &mut str {
        unsafe { str::from_utf8_unchecked_mut(&mut self.command) }
    }
}

impl Display for Prompt {
    fn fmt(&self, f: &mut std::fmt::Formatter<'_>) -> std::fmt::Result {
        Display::fmt(&**self, f)
    }
}
