#include "cli/parser.h"
#include "error.h"

#include <stdio.h>

const char* HELP = "usage: bd [OPTIONS] [PATH]\n"
				   "-h | --help\t showed this message.\n"
				   "-v | --version";

int main(const int argc, char* argv[argc + 1])
{
	Args args = {0};

	parseArgs(&args, argc, argv);
	CATCH({
		puts(getErrorMessage(Error.code));
		return EXIT_FAILURE;
	});

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