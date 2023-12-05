use crate::{cursor::free_goto, editor::Editor, error::Result, prompt::Prompt, render::Render};

pub trait PromptRenderer {
    fn render_prompt(&self, row_size: u16);
    fn suggest_prompt(&self);
}

impl PromptRenderer for Editor {
    fn render_prompt(&self, row_size: u16) {
        free_goto(row_size, 0);
        print!("=> {}", self.prompt);
    }

    fn suggest_prompt(&self) {
        todo!()
    }
}
