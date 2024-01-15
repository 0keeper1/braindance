use crate::{
    constants::clear,
    editor::Editor,
    render::EDITOR_FIRST_ROW_POSITION,
    settings::{EMPTY_LINE_CHARACTER, LINE_SEPARATOR},
};

pub trait RowRenderer {
    fn render_rows(&self, row_size: u16);
    fn line_number(&self, row: u16, file_end: u16);
}

impl RowRenderer for Editor {
    fn line_number(&self, row: u16, file_end: u16) {
        let end = file_end;

        if end < 9 {
            print!(" {row} {LINE_SEPARATOR} ")
        } else if end > 99 {
            print!(" {row}   {LINE_SEPARATOR} ")
        } else if end > 999 {
            print!(" {row}    {LINE_SEPARATOR} ")
        }
    }

    #[allow(clippy::print_with_newline)]
    fn render_rows(&self, row_size: u16) {
        // free_goto(EDITOR_FIRST_ROW_POSITION, 0);

        let file_position = self.render.get_position();

        let mut buf_iter = self.buffer.content.inner[file_position.start..file_position.end].iter();
        for _ in 1..(self.render.get_end_editor_position()) {
            print!("{}", clear::CLEAR_CURRENT_LINE);
            match buf_iter.next() {
                Some(row) => print!("{}", row),
                None => print!("{}", EMPTY_LINE_CHARACTER),
            }
            print!("\x1BE");
        }
    }
}
