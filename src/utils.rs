use std::ffi::OsStr;
use crate::{lines::Lines, row::Row, constants::{clear, cursors}};

pub trait ReadLines {
    fn lines(self) -> Lines;
}

impl ReadLines for Vec<u8> {
    #[inline]
    fn lines(self) -> Lines {
        Lines {
            inner: self
                .split(|char| char == &b'\n')
                .map(Row::from)
                .collect::<Vec<Row>>(),
        }
    }
}

#[inline]
pub fn clean_screen() {
    print!("{}{}", clear::CLEAR_ALL, clear::CLEAR_BUFFER);
}

#[inline]
pub fn hide_cursor() {
    print!("{}", cursors::CURSOR_HIDE);
}

pub fn file_prefix_to_language_name(file_prefix: Option<&OsStr>) -> &str {
    match file_prefix {
        Some(prefix) => match prefix.as_encoded_bytes() {
            b".asm" => "ASSEMBLY",
            b".h" | b".c" => "C",
            b".hpp" | b".cpp" => "C++",
            b".clj" => "CLOJURE",
            b".css" => "CSS",
            b".cfg" => "CONFIG",
            b".html" => "HTML",
            b".jl" => "JULIA",
            b".java" => "JAVA",
            b".json" => "JSON",
            b".js" => "JAVASCRIPT",
            b".kt" => "KOTLIN",
            b".lua" => "LUA",
            b".lisp" => "LISP",
            b".rs" => "RUST",
            b".rom" => "ROM",
            b".sh" => "SHELL",
            b".py" => "PYTHON",
            b".toml" => "TOML",
            b".php" => "PHP",
            b".vala" => "VALA",
            b".pony" => "PONY",
            b".sass" | b".scss" => "SASS",
            b"" => "",
            _ => "NOT SUPPORTED",
        },
        None => "NONE",
    }
}
