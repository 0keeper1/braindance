#include "cli/parser.h"

#include <linux/limits.h>
#include <stdlib.h>
#include <string.h>

bool isFlag(const char* const arg)
{
	const size_t len = strlen(arg);

	if (len == 2 && arg[0] == '-')
	{
		if (arg[1] == '-')
		{
			return false;
		}
		return true;
	}
	if (len > 2 && (arg[0] == '-' && arg[1] == '-'))
	{
		if (arg[2] == '-')
		{
			return false;
		}
		return true;
	}

	return false;
}
bool flagCmp(const char* arg, const char* small_flag, const char* large_flag)
{
	const size_t arg_len		= strlen(arg);
	const size_t small_flag_len = strlen(small_flag);
	const size_t large_flag_len = strlen(large_flag);

	if ((arg_len == small_flag_len &&
		 strncmp(arg, small_flag, small_flag_len) == 0) ||
		(arg_len == large_flag_len &&
		 strncmp(arg, large_flag, large_flag_len) == 0))
	{
		return true;
	}
	return false;
}

Args parseArgs(const int argc, const char*const argv[], ERR)
{
	Args args = {.path	  = {.cap = 0, .len = 0, .ptr = nullptr},
				 .cwd	  = {.cap = 0, .len = 0, .ptr = nullptr},
				 .help	  = false,
				 .version = false};

	if (argc > 4)
	{
		SET_ERR(CLI_ERR_TOO_MANY_ARGUMENTS, "Too many arguments");
		return args;
	}

	for (int i = 0; i < argc; ++i)
	{
		if (i == 0)
		{
			const size_t length = strlen(argv[0]);
			if ((args.cwd.ptr = (char*) malloc((length + 1) * sizeof(char))) ==
				nullptr)
			{
				SET_ERR(ERR_NULL_POINTER, "CWD allocation failed");
				return args;
			}
			args.cwd.cap = args.cwd.len = length;
			strncpy(args.cwd.ptr, argv[0], length);
		}
		if (isFlag(argv[i]))
		{
			if (flagCmp(argv[i], "-h", "--help"))
			{
				args.help = true;
				continue;
			}
			if (flagCmp(argv[i], "-v", "--version"))
			{
				args.version = true;
				continue;
			}
		}
		else
		{
			if (i != 0 && i == argc - 1)
			{
				if ((args.path.ptr = realpath(argv[i], nullptr)) != nullptr)
				{
					args.path.len = strlen(args.path.ptr);
					args.path.cap = PATH_MAX;
				}
			}
		}
	}
	return args;
}
