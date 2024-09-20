#pragma once

#include "cli.h"
#include "lines.h"
#include "info.h"
#include "offset.h"
#include "prompt.h"
#include "termios.h"

enum Layout {
	PROMPT,
	EDITOR,
};

typedef struct {
	Lines *lines;
	Prompt prompt;
	Offset offset;
	Info info;

	struct Terminal {
		u_int16_t row;
		u_int16_t col;
		struct termios termio;
	} terminal;

	enum Layout layout;

	bool exit;
} Core;

extern Core coreCreate();

extern Result coreInit(Core *const coreptr, const Cmds *const cmdsptr);

extern Result coreTermSizeUpdate(Core *const coreptr);

extern Result enableRawMode(Core *const coreptr);

extern Result disableRawMode(const Core *const coreptr);

extern void coreExit(const Core *const coreptr);

extern Result coreLoop(const Cmds *const cmdsptr);
