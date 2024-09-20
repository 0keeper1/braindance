cmake_minimum_required(VERSION 3.29)
project(braindance C)

set(CMAKE_C_STANDARD 23)

include_directories(src)
include_directories(src/cmdline)
include_directories(src/core)
include_directories(src/core/actions)
include_directories(src/core/buffer)
include_directories(src/core/display)

add_executable(braindance
    src/cmdline/cli.c
    src/cmdline/cli.h
    src/core/actions/commands.c
    src/core/actions/commands.h
    src/core/buffer/chars.c
    src/core/buffer/chars.h
    src/core/buffer/lines.c
    src/core/buffer/lines.h
    src/core/buffer/windowbuf.c
    src/core/buffer/windowbuf.h
    src/core/display/layouts.c
    src/core/display/layouts.h
    src/core/display/update.c
    src/core/display/update.h
    src/core/core.c
    src/core/core.h
    src/core/info.c
    src/core/info.h
    src/core/input.c
    src/core/input.h
    src/core/offset.c
    src/core/offset.h
    src/errors.c
    src/errors.h
    src/keybindings.h
    src/main.c
    src/options.h
    src/settings.h)
