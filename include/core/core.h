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

	bool skip;

	struct Terminal {
		u_int16_t row;
		u_int16_t col;
		struct termios termio;
	} terminal;

	enum Layout layout;

	bool exit;
} Core;

extern Core coreCreate();

extern Result coreInit(Core *const core_ptr, const Cmds *const cmds_ptr);

extern Result coreTermSizeUpdate(Core *const core_ptr);

extern Result enableRawMode(Core *const core_ptr);

extern Result disableRawMode(const Core *const core_ptr);

extern void coreExit(const Core *const core_ptr);

extern Result coreLoop(const Cmds *const cmds_ptr);
