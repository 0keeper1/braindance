use std::{io, ops::FromResidual};

pub type IoResult<T> = io::Result<T>;

pub type InternalResult<T> = Result<T, InternalError>;

pub type AppResult<T> = IoResult<InternalResult<T>>;

#[derive(Debug, Clone, Copy, PartialEq, Eq)]
pub enum InternalError {
    // Key Errors
    KeyDoesNotSupported,
    DurationTimeReached,
    MaximumKeyRepeatReached,

    // Terminal Errors
    MaximumTerminalSizeReached,
    MinimumTerminalSizeReached,

    // History Errors
    HistoryIsEmpty,
    HistoryFileNotFund,

    // Workspace Errors
    WorkspaceFolderDoesNotExists,

    // File Errors
    FileNotFound,
    PathIsNotAFile,
    PermissionDenied,
    AlreadyExists,
    ReadOnlyFilesystem,
    FileTooLarge,
    ResourceBusy,
    ExecutableFileBusy,
    ReadOnlyBuffer,
    FailedToWrite,
    OsError,

    // No Error
    NoError,
}

impl<'a> InternalError {
    pub fn to_str(self) -> &'a str {
        match self {
            // Key Error
            InternalError::MaximumKeyRepeatReached => "Maximum key repeat reached",
            InternalError::DurationTimeReached => "Duration time reached",
            InternalError::KeyDoesNotSupported => "Key Not Supported",

            // Terminal Error
            InternalError::MaximumTerminalSizeReached => "Maximum terminal size reached",
            InternalError::MinimumTerminalSizeReached => "Minimum terminal size reached",

            // History Errors
            InternalError::HistoryIsEmpty => "History is empty",
            InternalError::HistoryFileNotFund => "History file not found",

            // Workspace Errors
            InternalError::WorkspaceFolderDoesNotExists => "workspace folder does not exists",

            // File Errors
            InternalError::PathIsNotAFile => "Path is not a file",
            InternalError::PermissionDenied => "Permission denied",
            InternalError::ReadOnlyFilesystem => "File system is read only",
            InternalError::ExecutableFileBusy => "Executable file is busy",
            InternalError::FileNotFound => "File not found",
            InternalError::AlreadyExists => "File already exists",
            InternalError::FileTooLarge => "File is too large",
            InternalError::ResourceBusy => "File is busy",
            InternalError::ReadOnlyBuffer => "Buffer is read-only",
            InternalError::FailedToWrite => "Failed to write",
            InternalError::OsError => "Operation System error",

            // No Error
            InternalError::NoError => "",
        }
    }
}

impl<T> From<InternalError> for AppResult<T> {
    fn from(value: InternalError) -> Self {
        Self::Ok(Err(value))
    }
}

impl<T> FromResidual<InternalError> for AppResult<T> {
    fn from_residual(residual: InternalError) -> Self {
        Self::Ok(Err(residual))
    }
}
