#pragma once

#include <stdio.h>

typedef enum Result
{
	SUCCESSFUL,
	IO,
	FAILED,
	OUT_OF_MEMORY,
} Result;

void printErr( Result err );