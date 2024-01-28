pub mod clear {
    use crate::const_code;

    const_code!("2J", CLEAR_ALL);
    const_code!("3J", CLEAR_BUFFER);
    const_code!("4J", IDK);
    const_code!("J", CLEAR_AFTER_CURSOR);
    const_code!("1J", CLEAR_BEFORE_CURSOR);
    const_code!("2K", CLEAR_CURRENT_LINE);
    const_code!("K", CLEAR_NEW_LINE);
    pub const UPDATE_INITIALIZER: &str = concat!("\u{1b}[2J", "\u{1b}[3J", "\u{1b}[?25l");
    pub const DOUBLE_CLEAR: &str = concat!("\u{1b}[2J", "\u{1b}[3J");
}

pub mod colors {
    use crate::const_color;

    const_color!("30", COLOR_BLACK);
    const_color!("31", COLOR_RED);
    const_color!("32", COLOR_GREEN);
    const_color!("33", COLOR_YELLOW);
    const_color!("34", COLOR_BLUE);
    const_color!("35", COLOR_MAGNETA);
    const_color!("36", COLOR_CYAN);
    const_color!("37", COLOR_WHITE);
}

pub mod cursors {
    use crate::const_code;

    const_code!("?25l", CURSOR_HIDE);
    const_code!("?25h", CURSOR_SHOW);
}
