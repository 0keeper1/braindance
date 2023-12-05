use std::{io, result, str::FromStr};

pub type IoResult<T> = io::Result<T>;

pub type InternalResult<T> = result::Result<T, InternalError>;

pub type Result<T> = IoResult<InternalResult<T>>;

#[derive(Debug, Clone, Copy)]
pub enum InternalError {
    /// when path is directory not a file
    PathIsNotAFile,
    /// reach minimum size of terminal
    MinimumTerminalSizeReached,
    /// maximum size of terminal
    MaximumTerminalSizeReached,
    /// maximum key repeat
    MaximumKeyRepeatReached,
    /// duration time reached
    DurationTimeReached,
    /// key does not supported
    KeyDoesNotSupported,
    /// No Error
    NoError,
}

impl<'a> InternalError {
    pub fn to_str(self) -> &'a str {
        match self {
            InternalError::PathIsNotAFile => "Path is not a file.",
            InternalError::MinimumTerminalSizeReached => "Minimum terminal size reached",
            InternalError::MaximumTerminalSizeReached => "Maximum terminal size reached",
            InternalError::MaximumKeyRepeatReached => "Maximum key repeat reached",
            InternalError::DurationTimeReached => "Duration time reached",
            InternalError::NoError => "",
            InternalError::KeyDoesNotSupported => "Kek Not Supported",
        }
    }
}
