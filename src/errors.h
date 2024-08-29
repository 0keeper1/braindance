#pragma once

#include <stdio.h>

typedef enum Result
{
	SUCCESSFUL,
	FAILED,
	CLI_INVALID_FALG,
	OUT_OF_MEMORY,
} Result;

void printerr( Result err );