#pragma once

#include "../cmdline/cli.h"
#include "../errors.h"
#include "./buffer/lines.h"
#include "./buffer/windowbuf.h"
#include "./info.h"
#include "./offset.h"

#include <ctype.h>
#include <libgen.h>
#include <signal.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/ioctl.h>
#include <termios.h>
#include <unistd.h>

typedef struct {
	Lines *lines;
	Offset offset;
	Info info;
	// CommandLine commandline;
	// History history;
	bool exit;
} Core;

#include "./display/update.h"
#include "./input.h"

static struct termios ORGTERMIOS;

extern Result coreCreate(Core *const coreptr);

extern Result coreInit(Core *const coreptr, const Cmds *const cmdsptr);

extern Result enableRawMode();

extern Result disableRawMode();

extern void coreExit(Core *const coreptr);

extern Result coreLoop(const Cmds *const cmdsptr);
