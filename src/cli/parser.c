#include "cli/parser.h"

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
