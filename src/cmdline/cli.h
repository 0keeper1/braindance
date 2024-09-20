#pragma once

#include "../errors.h"
#include "../settings.h"

#include <limits.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

typedef struct {
	UTF *cwd;
	UTF *path;

	struct {
		bool help;
	} flags;
} Cmds;

extern Result createCmds(Cmds *const commands);

extern Result parseCli(const int argc, char *const argv[], Cmds *const commands);

extern Result checkPath(const char *const pathptr);

void freeCmds(const Cmds *const commands);
