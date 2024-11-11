#pragma once

#include "macros.h"

typedef struct Args
{
	STRING(cwd);
	STRING(path);
	bool version;
	bool help;
} Args;

extern bool isFlag(const char* arg);

extern bool flagCmp(const char* arg,
					const char* restrict small_flag,
					const char* restrict large_flag);

Args parseArgs(const int argc, const char* const argv[]);