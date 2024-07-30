#pragma once

#include "../cmdline/cli.h"
#include "../errors.h"
#include "./buffer/lines.h"
#include "./buffer/window.h"
#include "./fileh.h"
#include "./terminal/termutils.h"
#include <signal.h>
#include <stdbool.h>

typedef struct
{
	Lines *const lines;
	Window *const window; // handle window
	bool exit;
} Core;

extern Result coreLoop( Core *const core );
extern Core coreCreate( Lines *const lines, Window *const window );
extern Result coreRun( Cmds *const cmds );
