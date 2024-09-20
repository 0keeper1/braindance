#pragma once

#include "../core.h"

extern void writeHeaderBar(WindowBuf *winbufptr);

extern void writeSideBars(Core *const coreptr);

extern void writeFooterBar(Core *const coreptr);

extern void writeCommandBar(Core *const coreptr);

extern void writeContent(Core *const coreptr);

extern void writeLineNumber(Core *const coreptr);
