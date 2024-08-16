#pragma once

#include "../buffer/windowbuf.h"

extern void writeHeaderBar(  WindowBuf *const winbufptr );
extern void writeSideBars(  WindowBuf *const winbufptr );
extern void writeFooterBar(  WindowBuf *const winbufptr );
extern void writeCommandBar(  WindowBuf *const winbufptr );
extern void writeContent(  WindowBuf *const winbufptr );
extern void writeLineNumber(  WindowBuf *const winbufptr );