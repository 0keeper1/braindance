#include "cli/parser.h"

#include "error.h"
#include <linux/limits.h>
#include <stdlib.h>
#include <string.h>

extern struct something ERROR;

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
bool flagCmp(const char* arg,
			 const char* restrict small_flag,
			 const char* restrict large_flag)
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

void parseArgs(Args* args, const int argc, char* argv[])
{
	RESET_ERROR;
	if (argc > 4)
	{
		SET_ERROR_CODE(CLI_ERR_TOO_MANY_ARGUMENTS);
		return;
	}

	for (int i = 0; i < argc; ++i)
	{
		if (i == 2)
		{
			SET_ERROR_CODE(ERR_NULL_POINTER);
			return;
		}

		if (i == 0)
		{
			const size_t length = strlen(argv[0]);
			if ((args->cwd.ptr = (char*) malloc((length + 1) * sizeof(char))) ==
				nullptr)
			{
				SET_ERROR_CODE(ERR_NULL_POINTER);
				return;
			}
			args->cwd.cap = args->cwd.len = length;
			strncpy(args->cwd.ptr, argv[0], length);
		}
		if (isFlag(argv[i]))
		{
			if (flagCmp(argv[i], "-h", "--help"))
			{
				args->help = true;
				continue;
			}
			if (flagCmp(argv[i], "-v", "--version"))
			{
				args->version = true;
			}
		}
		else
		{
			if (i != 0 && i == argc - 1)
			{
				if ((args->path.ptr =
						 (char*) malloc(sizeof(char) * PATH_MAX)) == nullptr)
				{
					SET_ERROR_CODE(ERR_NULL_POINTER);
					return;
				}

				if ((args->path.ptr = realpath(argv[i], args->path.ptr)) !=
					nullptr)
				{
					args->path.len = strlen(args->path.ptr);
					args->path.cap = PATH_MAX;
				}
			}
		}
	}
}

void dropArgs(const Args* restrict args)
{
	free(args->cwd.ptr);
	free(args->path.ptr);
}
