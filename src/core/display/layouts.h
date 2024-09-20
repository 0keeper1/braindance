#pragma once

#include "../core.h"

extern void writeHeaderBar(WindowBuf *const winbufptr, const u_int16_t col, const u_int16_t row);

extern void writeSideBars(WindowBuf *const winbufptr);

extern void writeFooterBar(WindowBuf *const winbufptr, const u_int16_t col, const u_int16_t row);

extern void writeCommandBar(WindowBuf *const winbufptr, const u_int16_t col, const u_int16_t row);

extern void writeContent(WindowBuf *const winbufptr);

extern void writeLineNumber(WindowBuf *const winbufptr, const u_int16_t row);
