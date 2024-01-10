use std::path::{PathBuf, Path};

use crate::{
    buffer::{Buffer, Mode},
    counter::Counter,
    event::EventHandler,
    prelude::*,
    prompt::Prompt,
    render::Render,
    terminal::Terminal,
    update::Update,
    utils::clean_screen,
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
    pub terminal: Terminal, // store terminal size and raw Stdout
    pub render: Render,     // rendering the display
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
            terminal: Terminal::new(),
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

    fn change_workspace(&mut self, path: &Path) {
        println!("change workspace");
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

    fn init(&mut self) -> IoResult<()> {
        simple_logging::log_to_file("test.log", LevelFilter::Info)?;

        self.terminal.enable_raw_mode()?;

        match self.terminal.initialize_size()? {
            Ok(..) => info!("Initialize the size of terminal."),
            Err(err) => self.internal_error = err,
        };
        let terminal_row_size = self.terminal.get_row_size();

        self.render.set_end_editor_position(terminal_row_size);

        self.render.update(self.buffer.len());

        info!("initialized.");

        info!("{:?}", self.render);

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


#[cfg(test)]
mod tests {
    use std::path::PathBuf;

    use super::Editor;

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
}