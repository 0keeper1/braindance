#pragma once

#include "../cmdline/cli.h"
#include "../errors.h"
#include "./buffer/lines.h"
#include "./buffer/windowbuf.h"
#include "./offset.h"
#include <signal.h>
#include <stdbool.h>
#include <stdio.h>
#include <sys/ioctl.h>
#include <termios.h>
#include <unistd.h>

typedef struct
{
	Lines *const lines;
	WindowBuf const window;
	Offset const offset;
	bool exit;
} Core;

Result coreLoop( Core *const core );
Result coreInit();
FILE *fileOpen( char *const path, const char *const mode );
void coreExit();

extern Result coreRun( const Cmds *const cmds );