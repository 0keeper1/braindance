#include "cli/parser.h"
#include "error.h"

#include <stdio.h>

const char* HELP = "usage: bd [OPTIONS] [FILE PATH]\n"
				   "-h | --help\tShowed this message.\n"
				   "-v | --version";

int main(const int argc, const char* const argv[])
{
	ERROR;

	Args args = {0};

	args = parseArgs(argc, argv, &error);
	if (error.code != NOTSET)
	{
		printf("%s\n", error.message.ptr);
		FE_ERROR;
		return EXIT_FAILURE;
	}

	if (args.help == true)
	{
		puts(HELP);
		FE_ERROR;
		return EXIT_SUCCESS;
	}
	if (args.version == true)
	{
		puts(VERSION);
		FE_ERROR;
		return EXIT_SUCCESS;
	}

	return 0;
}