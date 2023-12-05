#[macro_export]
macro_rules! const_code {
    ($code:expr, $name:ident) => {
        pub const $name: &str = concat!("\x1B[", $code);
    };
}

#[macro_export]
macro_rules! const_color {
    ($code:expr, $name:ident) => {
        pub const $name: &str = concat!("\x1B[", $code, 'm');
    };
}
