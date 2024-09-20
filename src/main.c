#include "./cmdline/cli.h"
#include "./core/core.h"
#include "./errors.h"
#include "./settings.h"

#include <stdio.h>
#include <stdlib.h>

const char *HELP = "usage: bd [OPTIONS] <FILE PATH>\n\t-h | --help\tShowed this message.\n\r";

int main(const int argc, char *argv[]) {
	Cmds commands;
	if (createCmds(&commands) == OUT_OF_MEMORY) {
		return EXIT_FAILURE;
	}
	if (parseCli(argc, argv, &commands) == CLI_INVALID_FALG) {
		puts("Invalid input flag.\n");
		return EXIT_FAILURE;
	}

	if (commands.flags.help == true) {
		puts(HELP);
		return EXIT_SUCCESS;
	} else if (commands.path == NULL) {
		fprintf(stderr, "Enter a specific file path to edit.\n");
		return EXIT_FAILURE;
	}

	if (coreLoop(&commands) == SUCCESSFUL) {
		return EXIT_SUCCESS;
	}

	freeCmds(&commands);
	return EXIT_FAILURE;
}
