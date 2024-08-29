#pragma once

#include "../errors.h"
#include <limits.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

typedef struct
{
	char *cwd;
	char *path;
	struct
	{
		bool help;
	} flags;
} Cmds;

Cmds createCmds();
Result parseCli( int argc, char *const argv[], Cmds *const commands );
