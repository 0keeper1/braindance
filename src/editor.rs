use std::path::{Path, PathBuf};

use crate::{
    buffer::{Buffer, Mode},
    counter::Counter,
    event::EventHandler,
    prelude::*,
    prompt::Prompt,
    render::Render,
    size::{RowCol, TerminalSize},
    update::Update,
    utils::{clean_screen, TerminalMode},
};

use log::{info, LevelFilter};

#[derive(Debug)]
pub enum Layouts {
    Prompt,
    Editor,
}

#[derive(Debug)]
pub struct Editor {
    pub buffer: Buffer, // just one buffer at time
    /// workspace directory can be a current path or given path from terminal
    pub dir: PathBuf, // workspace directory
    pub prompt: Prompt, // prompt for getting commands
    pub counter: Counter,
    /// focus on Editor or Prompt
    pub layout: Layouts,
    pub terminal_size: RowCol, // store terminal size and raw Stdout
    pub render: Render,        // rendering the display
    pub internal_error: InternalError,
    pub exit: bool, // exit signal
}

impl Editor {
    pub fn new() -> Self {
        Self {
            buffer: Buffer::new(),
            dir: PathBuf::new(),
            prompt: Prompt::new(),
            counter: Counter::new(),
            layout: Layouts::Editor,
            terminal_size: RowCol::default(),
            render: Render::new(),
            internal_error: InternalError::NoError,
            exit: false,
        }
    }

    #[inline]
    pub fn set_error(&mut self, error: InternalError) {
        self.internal_error = error;
    }

    #[inline]
    pub fn set_no_error(&mut self) {
        self.internal_error = InternalError::NoError;
    }

    #[inline]
    fn change_workspace(&mut self, path: &Path) {
        self.dir = path.to_path_buf();
    }

    #[inline]
    fn remove_workspace(&mut self) {
        self.dir.clear()
    }

    pub fn init_path(&mut self, path: &Path) -> IoResult<()> {
        if path.is_dir() {
            self.dir.push(path)
        } else if path.is_file() {
            match self.buffer.open(path, Mode::ReadWrite)? {
                Ok(..) => (),
                Err(err) => self.set_error(err),
            };
        };
        Ok(())
    }

    fn setup_terminal_settings(&mut self) -> IoResult<()> {
        self.enable_raw_mode()?;
        self.terminal_size.update_size()?;
        Ok(())
    }

    fn init(&mut self) -> IoResult<()> {
        simple_logging::log_to_file("test.log", LevelFilter::Info)?;
        self.setup_terminal_settings()?;
        Ok(())
    }

    fn shutdown(&self) {
        clean_screen();
        println!("BD Closed.");
        info!("shutdown")
    }

    pub fn run(&mut self) -> IoResult<()> {
        self.init()?;

        loop {
            self.update()?;
            self.event()?;
            if self.exit {
                break;
            }
        }

        self.shutdown();
        Ok(())
    }
}

impl TerminalMode for Editor {}

#[cfg(test)]
mod tests {
    use std::path::PathBuf;

    use crossterm::terminal::is_raw_mode_enabled;

    use super::Editor;
    use crate::{size::TerminalSize, utils::TerminalMode, InternalError};

    #[test]
    fn set_folder_path() {
        let path = PathBuf::from("./src/");

        let mut editor = Editor::new();

        match editor.init_path(&path) {
            Ok(()) => (),
            Err(err) => todo!("{err}"),
        };

        assert_eq!(editor.dir, path)
    }

    #[test]
    fn set_file_path() {
        let path = PathBuf::from("./src/buffer.rs");

        let mut editor = Editor::new();

        match editor.init_path(&path) {
            Ok(()) => (),
            Err(err) => todo!("{err}"),
        };

        assert_eq!(editor.buffer.path, path)
    }

    #[test]
    #[ignore = "not working on github workflow"]
    fn enable_raw_mode() {
        let mut editor = Editor::new();
        editor.enable_raw_mode().unwrap();

        assert!(is_raw_mode_enabled().unwrap());

        crossterm::terminal::disable_raw_mode().unwrap();
    }

    #[test]
    #[ignore = "not working on github workflow"]
    fn disable_raw_mode() {
        let mut editor = Editor::new();
        editor.enable_raw_mode().unwrap();
        editor.disable_raw_mode().unwrap();

        assert!(is_raw_mode_enabled().unwrap());
    }

    #[test]
    #[ignore = "not working on github workflow"]
    fn reach_minimum_terminal_size() {
        let mut editor = Editor::new();

        let result = editor.terminal_size.update_size().expect("IO error");
        match result {
            Ok(..) => panic!("must be panic"),
            Err(err) => assert_eq!(err, InternalError::MinimumTerminalSizeReached),
        }
    }
}
