#pragma once

#include "../errors.h"

typedef struct {
	char *cwd;
	char *path;

	struct {
		bool help;
	} flags;
} Cmds;

extern Result createCmds(Cmds *const commands_ptr);

extern Result parseCli(const int argc, char *const argv[], Cmds *const commands_ptr);

void freeCmds(const Cmds *const commands_ptr);
