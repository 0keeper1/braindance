use super::BarRenderer;
use crate::{
    cursor::free_goto,
    error::Result,
    utils::{clean_screen, hide_cursor},
    VERSION, render::Render, editor::TERMINAL_SIZE,
};

pub trait MenuRenderer: BarRenderer {
    fn render_menu(&self) -> Result<()>;
}

impl MenuRenderer for Render {
    fn render_menu(&self) -> Result<()> {
        hide_cursor();

        clean_screen();
        let (terminal_width, terminal_height) = unsafe { TERMINAL_SIZE.into() };

        let middle_of_screen = terminal_width / 2 - 6;
        let center_of_screen = terminal_height / 2;

        self.draw_buffer_line()?;

        free_goto(middle_of_screen, center_of_screen - 46);
        print!("                              ,,                    ,,                                        ");
        free_goto(middle_of_screen + 1, center_of_screen - 46);
        print!(
            r#"`7MM"""Yp,                    db                  `7MM                                        "#
        );
        free_goto(middle_of_screen + 2, center_of_screen - 46);
        print!("  MM    Yb                                          MM                                        ");
        free_goto(middle_of_screen + 3, center_of_screen - 46);
        print!(
            r#"  MM    dP `7Mb,od8 ,6"Yb.  `7MM  `7MMpMMMb.   ,M""bMM   ,6"Yb.  `7MMpMMMb.  ,p6"bo   .gP"Ya  "#
        );
        free_goto(middle_of_screen + 4, center_of_screen - 46);
        print!(
            r#"  MM"""bg.   MM' "'8)   MM    MM    MM    MM ,AP    MM  8)   MM    MM    MM 6M'  OO  ,M'   Yb "#
        );
        free_goto(middle_of_screen + 5, center_of_screen - 46);
        print!(
            r#"  MM    `Y   MM     ,pm9MM    MM    MM    MM 8MI    MM   ,pm9MM    MM    MM 8M       8M"""""" "#
        );
        free_goto(middle_of_screen + 6, center_of_screen - 46);
        print!(
            r#"  MM    ,9   MM    8M   MM    MM    MM    MM `Mb    MM  8M   MM    MM    MM YM.    , YM.    , "#
        );
        free_goto(middle_of_screen + 7, center_of_screen - 46);
        print!(
            r#".JMMmmmd9  .JMML.  `Moo9^Yo..JMML..JMML  JMML.`Wbmd"MML.`Moo9^Yo..JMML  JMML.YMbmd'   `Mbmmd' "#
        );

        let start_menu_position = middle_of_screen + 10;
        free_goto(start_menu_position, center_of_screen - 5);
        print!("\x1b[31;2m⊳\x1b[0m Open File");

        free_goto(start_menu_position + 2, center_of_screen - 7);
        print!("\x1b[31;2m⊳\x1b[0m Open Workspace");

        free_goto(start_menu_position + 4, center_of_screen - 6);
        print!("\x1b[31;2m►\x1b[0m Open Folder");

        free_goto(start_menu_position + 6, center_of_screen - 3);
        print!("\x1b[31;2m⊳\x1b[0m Exit");

        let info_line_position = start_menu_position + 9;

        free_goto(info_line_position, center_of_screen - 46);
        print!("There Is Nothing We Can Do ...");

        free_goto(info_line_position, center_of_screen + (46 - 12));
        print!("Version {}", VERSION);

        self.draw_bar("NO FILE", "NONE")?;

        Ok(())
    }
}
