use std::time::{Duration, Instant};

use crossterm::event::{KeyCode, KeyModifiers};

use crate::{
    prelude::*,
    settings::{MAXIMUM_KEY_DURATION_TIME, MAXIMUM_KEY_REPEAT_LIMIT},
};

// -- config --
const MAXIMUM_REPEAT: u8 = MAXIMUM_KEY_REPEAT_LIMIT;
const MAXIMUM_DURATION: Duration = Duration::from_millis(MAXIMUM_KEY_DURATION_TIME);
// -- end --

#[derive(Debug)]
/// counting the repeat key (keybinding)
/// just for ALT, CTRL, HOME modifiers
pub struct Counter {
    modifier: KeyModifiers,
    keycode: KeyCode,
    /// counter range between 0..MAXIMUM_KEY_REPEAT_LIMIT
    counter: u8,
    /// save first key event time
    start_time: Instant,
}

impl Counter {
    pub fn new() -> Self {
        Self {
            modifier: KeyModifiers::NONE,
            keycode: KeyCode::Null,
            counter: 0,
            start_time: Instant::now(),
        }
    }

    pub fn clear_counter(&mut self) {
        self.counter = 0;
        self.keycode = KeyCode::Null;
        self.modifier = KeyModifiers::NONE;
    }

    fn first_event(&mut self, modifier: KeyModifiers, key: KeyCode) {
        self.start_time = Instant::now();
        self.counter += 1;
        self.keycode = key;
        self.modifier = modifier;
    }

    fn update_counter(&mut self) {
        self.start_time = Instant::now();
        self.counter += 1;
    }

    pub fn modifier_key_event(
        &mut self,
        modifier: KeyModifiers,
        key: KeyCode,
    ) -> InternalResult<()> {
        if self.counter == 0 || self.modifier != modifier && key != self.keycode {
            self.first_event(modifier, key);
            return Ok(());
        };

        if self.start_time.elapsed() > MAXIMUM_DURATION {
            self.clear_counter();
            return Err(InternalError::DurationTimeReached);
        }

        if self.counter + 1 > MAXIMUM_REPEAT {
            self.clear_counter();
            return Err(InternalError::MaximumKeyRepeatReached);
        }

        if self.counter + 1 > 1 {
            self.update_counter();
            return Ok(());
        };

        Ok(())
    }

    fn get_key_event(&self) -> (u8, KeyModifiers, KeyCode) {
        (self.counter, self.modifier, self.keycode)
    }

    pub fn execute(&mut self) -> (u8, KeyModifiers, KeyCode) {
        return self.get_key_event();
        self.clear_counter();
    }
}
