#pragma once

#include "../cmdline/cli.h"
#include "../errors.h"
#include "./buffer/lines.h"
#include "./buffer/window.h"
#include "./fileh.h"

typedef struct
{
	Lines *const lines;
	Window *const window; // handle window
	bool exit;
} Core;

extern Result loop( Core *const core );
extern Core coreCreate();
extern Result coreRun( Cmds *const cmds );
