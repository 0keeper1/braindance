#![feature(io_error_more, path_file_prefix, file_create_new)]
#![allow(unused)]

mod buffer;
mod constants;
mod counter;
mod cursor;
mod editor;
mod error;
mod event;
mod history;
mod lines;
mod macros;
mod prelude;
mod prompt;
mod range;
mod render;
mod row;
mod settings;
mod terminal;
mod update;
mod utils;

use std::{env, path::PathBuf};

use editor::Editor;
use prelude::*;

const VERSION: &str = env!("CARGO_PKG_VERSION");

fn main() -> IoResult<()> {
    let mut args = env::args_os();

    let mut editor = Editor::new();

    if let Some(path) = args.nth(1) {
        let location = PathBuf::from(path);
        editor.init_path(location)?;
    }

    editor.run()?;
    Ok(())
}
