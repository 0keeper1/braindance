#pragma once

#include "../cmdline/cli.h"
#include "../errors.h"
#include "./buffer/lines.h"
#include "./buffer/windowbuf.h"
#include "./offset.h"
#include <ctype.h>
#include <signal.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/ioctl.h>
#include <termios.h>
#include <unistd.h>

typedef struct
{
	Lines *const lines;
	WindowBuf window;
	Offset offset;
	bool exit;
} Core;

#include "./display/update.h"
#include "./input.h"

static struct termios ORGTERMIOS;

Result coreLoop( Core *const core );
Result coreInit();
FILE *fileOpen( char *const path, const char *const mode );
Result enableRawMode();
Result disableRawMode();
void coreExit();

extern Result coreRun( const Cmds *const cmds );