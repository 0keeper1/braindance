#include "cli.h"
#include "../errors.h"

#include <limits.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>


bool isFlag(const char *const arg_ptr) {
	if (arg_ptr[0] == '-' || (arg_ptr[0] == '-' && arg_ptr[1] == '-')) {
		return true;
	}
	return false;
}

bool checkFlag(const char *const argument, const char *const small_flag_ptr, const char *const large_flag_ptr) {
	return strncmp(argument, small_flag_ptr, strlen(small_flag_ptr)) == 0 ||
	       strncmp(argument, large_flag_ptr, strlen(large_flag_ptr)) == 0;
}

Result createCmds(Cmds *const commands_ptr) {
	char *cwdptr = calloc(PATH_MAX, sizeof(char));

	if (cwdptr == nullptr) {
		return FAILED;
	}

	commands_ptr->cwd = cwdptr;
	commands_ptr->path = nullptr;
	commands_ptr->flags.help = false;

	return SUCCESSFUL;
}

Result parseCli(const int argc, char *const argv[], Cmds *const commands_ptr) {
	for (int c = 1; c != argc; c++) {
		if (isFlag(argv[c])) {
			if (checkFlag(argv[c], "-h", "--help")) {
				commands_ptr->flags.help = true;
				return SUCCESSFUL;
			}
			return FAILED;
		}
		if (c == (argc - 1)) {
			commands_ptr->path = realpath(argv[c], nullptr);
		}
	}
	commands_ptr->cwd = getcwd(commands_ptr->cwd, PATH_MAX);
	return SUCCESSFUL;
}

[[gnu::always_inline]]
inline void freeCmds(const Cmds *const commands_ptr) {
	free(commands_ptr->cwd);
}
