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

    #[inline]
    pub fn clear_counter(&mut self) {
        self.counter = 0;
        self.keycode = KeyCode::Null;
        self.modifier = KeyModifiers::NONE;
    }

    #[inline]
    fn first_event(&mut self, modifier: KeyModifiers, key: KeyCode) {
        self.start_time = Instant::now();
        self.counter = 1;
        self.keycode = key;
        self.modifier = modifier;
    }

    #[inline]
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

    pub fn execute(&mut self) {
        todo!()
    }
}

#[cfg(test)]
mod tests {
    use std::{thread, time::Duration};

    use crossterm::event::{KeyCode, KeyEvent, KeyModifiers};

    use crate::{prelude::InternalError, settings::MAXIMUM_KEY_DURATION_TIME};

    use super::Counter;

    #[test]
    fn one_event() {
        let event = KeyEvent::new(KeyCode::Char('x'), KeyModifiers::CONTROL);
        let mut counter = Counter::new();

        counter
            .modifier_key_event(event.modifiers, event.code)
            .unwrap();

        assert_eq!(counter.counter, 1);
    }

    #[test]
    fn two_event() {
        let event = KeyEvent::new(KeyCode::Char('x'), KeyModifiers::CONTROL);
        let mut counter = Counter::new();

        counter
            .modifier_key_event(event.modifiers, event.code)
            .unwrap();
        counter
            .modifier_key_event(event.modifiers, event.code)
            .unwrap();

        assert_eq!(counter.counter, 2);
    }

    #[test]
    fn three_event() {
        let event = KeyEvent::new(KeyCode::Char('x'), KeyModifiers::CONTROL);
        let mut counter = Counter::new();

        counter
            .modifier_key_event(event.modifiers, event.code)
            .unwrap();
        counter
            .modifier_key_event(event.modifiers, event.code)
            .unwrap();
        counter
            .modifier_key_event(event.modifiers, event.code)
            .unwrap();

        assert_eq!(counter.counter, 3);
    }

    #[test]
    fn reach_duration_time() {
        let event = KeyEvent::new(KeyCode::Char('x'), KeyModifiers::CONTROL);
        let mut counter = Counter::new();

        let result = counter.modifier_key_event(event.modifiers, event.code);
        assert!(result.is_ok());

        thread::sleep(Duration::from_millis(MAXIMUM_KEY_DURATION_TIME - 50));

        let result = counter.modifier_key_event(event.modifiers, event.code);
        assert!(result.is_ok());

        thread::sleep(Duration::from_millis(MAXIMUM_KEY_DURATION_TIME + 100));

        let result = counter.modifier_key_event(event.modifiers, event.code);
        match result {
            Ok(..) => panic!("must be error"),
            Err(err) => assert_eq!(err, InternalError::DurationTimeReached),
        }
    }

    #[test]
    fn change_event() {
        let event = KeyEvent::new(KeyCode::Char('x'), KeyModifiers::CONTROL);
        let second_event = KeyEvent::new(KeyCode::Char('f'), KeyModifiers::ALT);

        let mut counter = Counter::new();

        counter
            .modifier_key_event(event.modifiers, event.code)
            .unwrap();

        let _ = counter.modifier_key_event(second_event.modifiers, second_event.code);
        assert_eq!(counter.counter, 1);
        assert_eq!(counter.keycode, second_event.code);
        assert_eq!(counter.modifier, second_event.modifiers);
    }

    #[test]
    fn reach_maximum_repeat_limit() {
        let event = KeyEvent::new(KeyCode::Char('x'), KeyModifiers::CONTROL);
        let mut counter = Counter::new();

        counter
            .modifier_key_event(event.modifiers, event.code)
            .unwrap();
        counter
            .modifier_key_event(event.modifiers, event.code)
            .unwrap();
        counter
            .modifier_key_event(event.modifiers, event.code)
            .unwrap();

        let result = counter.modifier_key_event(event.modifiers, event.code);
        match result {
            Ok(..) => panic!("must be error"),
            Err(err) => assert_eq!(err, InternalError::MaximumKeyRepeatReached),
        }
    }

    #[test]
    fn continue_event_after_reach_max_limit() {
        let event = KeyEvent::new(KeyCode::Char('x'), KeyModifiers::CONTROL);
        let mut counter = Counter::new();

        counter
            .modifier_key_event(event.modifiers, event.code)
            .unwrap();
        counter
            .modifier_key_event(event.modifiers, event.code)
            .unwrap();
        counter
            .modifier_key_event(event.modifiers, event.code)
            .unwrap();

        let result = counter.modifier_key_event(event.modifiers, event.code);
        match result {
            Ok(..) => panic!("must be error"),
            Err(err) => assert_eq!(err, InternalError::MaximumKeyRepeatReached),
        }

        counter
            .modifier_key_event(event.modifiers, event.code)
            .unwrap();
        assert_eq!(counter.counter, 1);
        assert_eq!(counter.keycode, event.code);
        assert_eq!(counter.modifier, event.modifiers);
    }

    #[test]
    fn continue_event_after_duration_time() {
        let event = KeyEvent::new(KeyCode::Char('x'), KeyModifiers::CONTROL);
        let mut counter = Counter::new();

        let result = counter.modifier_key_event(event.modifiers, event.code);
        assert!(result.is_ok());
        let result = counter.modifier_key_event(event.modifiers, event.code);
        assert!(result.is_ok());

        thread::sleep(Duration::from_millis(MAXIMUM_KEY_DURATION_TIME + 50));

        let result = counter.modifier_key_event(event.modifiers, event.code);
        match result {
            Ok(..) => panic!("must be error"),
            Err(err) => assert_eq!(err, InternalError::DurationTimeReached),
        }

        counter
            .modifier_key_event(event.modifiers, event.code)
            .unwrap();
        assert_eq!(counter.counter, 1);
        assert_eq!(counter.keycode, event.code);
        assert_eq!(counter.modifier, event.modifiers);
    }
}
