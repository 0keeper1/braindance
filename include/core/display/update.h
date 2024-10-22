#pragma once

#include "../../errors.h"
#include "../buffer/windowbuf.h"
#include "../core.h"

#define SCREEN_CLEAR "\x1b[2J"

#define BUFFER_CLEAR "\x1b[3J"

#define CURSOR_AT_START "\x1b[H"

#define HIDE_CURSOR "\x1b[?25l"

#define SHOW_CURSOR "\x1b[?25h"

extern Result display(const Core *const coreptr);

extern void restoreCursor(WindowBuf *const winbufptr, const Prompt *const promptptr,
                          const u_int16_t col, const u_int16_t row,
                          const u_int16_t cursorcolpos, const u_int16_t cursorrowpos,
                          const enum Layout layout);
