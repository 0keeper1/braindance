#pragma once

#include "../errors.h"
#include "../settings.h"

typedef struct {
	char *cwd;
	char *path;

	struct {
		bool help;
	} flags;
} Cmds;

extern Result createCmds(Cmds *const commands);

extern Result parseCli(const int argc, char *const argv[], Cmds *const commands);

extern Result checkPath(const char *const pathptr);

void freeCmds(const Cmds *const commands);
