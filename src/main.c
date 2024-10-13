#include <stdio.h>
#include <stdlib.h>

#include "./cmdline/cli.h"
#include "./core/core.h"
#include "./errors.h"

const char *HELP = "usage: bd [OPTIONS] <FILE PATH>\n\t-h | --help\tShowed this message.\n\r";

int main() {
#include "./core/buffer/content.h"
	testContentReadFromFile();
}

// int main(const int argc, char *argv[]) {
// 	Cmds commands;
// 	if (createCmds(&commands) == FAILED) {
// 		return EXIT_FAILURE;
// 	}
// 	if (parseCli(argc, argv, &commands) == FAILED) {
// 		puts("Invalid input flag.\n");
// 		return EXIT_FAILURE;
// 	}
//
// 	if (commands.flags.help == true) {
// 		puts(HELP);
// 		return EXIT_SUCCESS;
// 	} else if (commands.path == nullptr) {
// 		fprintf(stderr, "Enter a specific file path to edit.\n");
// 		return EXIT_FAILURE;
// 	}
//
// 	if (coreLoop(&commands) == SUCCESSFUL) {
// 		return EXIT_SUCCESS;
// 	}
//
// 	freeCmds(&commands);
// 	return EXIT_FAILURE;
// }
