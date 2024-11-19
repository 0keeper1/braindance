#pragma once

#include "macros.h"

typedef struct Args
{
	STRING(cwd);
	STRING(path);
	bool version;
	bool help;
} Args;

bool isFlag(const char* arg);

bool flagCmp(const char* arg,
			 const char* restrict small_flag,
			 const char* restrict large_flag);

extern void parseArgs(Args* args, int argc, char* argv[]);

extern void dropArgs(const Args* restrict args);
