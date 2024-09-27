#include "cli.h"
#include "../errors.h"

#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>


bool isFlag(const char *const arg) {
	if (arg[0] == '-' || (arg[0] == '-' && arg[1] == '-')) {
		return true;
	} else {
		return false;
	}
}

bool checkFlag(const char *const argument, const char *const small_flag, const char *const large_flag) {
	return strncmp(argument, small_flag, strlen(small_flag)) == 0 ||
	       strncmp(argument, large_flag, strlen(large_flag)) == 0;
}

Result createCmds(Cmds *const commands) {
	char *cwdptr = calloc(PATH_MAX, sizeof(char));

	if (cwdptr == nullptr) {
		return FAILED;
	}

	commands->cwd = cwdptr;
	commands->path = nullptr;
	commands->flags.help = false;

	return SUCCESSFUL;
}

Result parseCli(const int argc, char *const argv[], Cmds *const commands) {
	for (int c = 1; c != argc; c++) {
		if (isFlag(argv[c])) {
			if (checkFlag(argv[c], "-h", "--help")) {
				commands->flags.help = true;
				return SUCCESSFUL;
			}
			return FAILED;
		}
		if (c == (argc - 1)) {
			commands->path = (char *) realpath(argv[c], nullptr);
		}
	}
	commands->cwd = getcwd((char *) commands->cwd, PATH_MAX);
	return SUCCESSFUL;
}

void freeCmds(const Cmds *const commands) {
	free(commands->cwd);
}
