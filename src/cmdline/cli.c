#include "cli.h"

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
	UTF *cwdptr = calloc(PATH_MAX, sizeof(UTF));
	if (cwdptr == NULL) {
		return OUT_OF_MEMORY;
	}

	commands->cwd = cwdptr;
	commands->path = NULL;
	commands->flags.help = false;

	return SUCCESSFUL;
}

Result parseCli(const int argc, char *const argv[], Cmds *const commands) {
	for (int c = 1; c != argc; c++) {
		if (isFlag(argv[c])) {
			if (checkFlag(argv[c], "-h", "--help")) {
				commands->flags.help = true;
				return SUCCESSFUL;
			} else {
				return CLI_INVALID_FALG;
			}
		} else if (c == (argc - 1)) {
			commands->path = (UTF *) realpath(argv[c], NULL);
		}
	}
	commands->cwd = (UTF *) getcwd((char *) commands->cwd, PATH_MAX);
	return SUCCESSFUL;
}

void freeCmds(const Cmds *const commands) {
	free(commands->cwd);
}
