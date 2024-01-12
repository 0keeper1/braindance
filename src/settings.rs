use crossterm::event::KeyCode;

// -- Core Section--

pub const TITLE_BAR: &str = concat!("\x1b[7mBRAINDANCE ", env!("CARGO_PKG_VERSION"), "\x1b[0m");

pub const MAXIMUM_KEY_REPEAT_LIMIT: u8 = 3;
/// best choice between 200 .. 400
pub const MAXIMUM_KEY_DURATION_TIME: u64 = 200;

pub const EMPTY_LINE_CHARACTER: char = '~';

/// best options is |│┃
pub const LINE_SEPARATOR: char = '│';
/// if true show line number else doesn't show
pub const LINE_NUMBER: bool = false;
// -- --

/// Key to Exit the editor
pub const EXIT_KEY: KeyCode = KeyCode::Char('q');

/// How Many Times to Exit
pub const EXIT_TIMES: u8 = 2;
/// How Many Times to Force Exit
pub const EXIT_FORCE_TIMES: u8 = 3;

/// Save
pub const SAVE: KeyCode = KeyCode::Char('s');
/// How Many Times to SAVE
pub const SAVE_TIMES: u8 = 1;

pub const LINE_NUMBER_COLOR: (u8, u8, u8) = (129, 222, 255);
