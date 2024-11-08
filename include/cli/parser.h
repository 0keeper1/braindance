#pragma once

#include "error.h"

typedef struct Args
{
	STRING(cwd);
	STRING(path);
	bool verbose;
	bool help;
} Args;

extern bool isFlag(const char* const arg);

extern bool flagCmp(const char* arg,
					const char* restrict small_flag,
					const char* restrict large_flag);

Args parseArgs(const int argc, const char** argv, ERR);