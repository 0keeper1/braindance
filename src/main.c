#include "cli/parser.h"
#include "error.h"

#include <stdio.h>

const char* HELP = "usage: bd [OPTIONS] [PATH]\n"
				   "-h | --help\t showed this message.\n"
				   "-v | --version";

int main(const int argc, const char* const argv[])
{
	Args args = {0};

	args = parseArgs(argc, argv);
	CATCH_ERROR(CLI_ERR_TOO_MANY_ARGUMENTS, {
		puts(HELP);
		return EXIT_FAILURE;
	})

	if (args.help == true)
	{
		puts(HELP);
		return EXIT_SUCCESS;
	}
	if (args.version == true)
	{
		puts(VERSION);
		return EXIT_SUCCESS;
	}

	return 0;
}