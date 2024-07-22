#pragma once

#include "../errors.h"
#include <stdio.h>
#include <string.h>
#include <unistd.h>

typedef struct
{
	char *cwd;
	char *path;
	bool help;
} Cmds;

Cmds createCmds();
Result parseCli( int argc, const char *const argv[], Cmds *const commands );
