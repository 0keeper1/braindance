#pragma once

#include "../../settings.h"

struct Window
{
	unsigned int cap; // mul width and height
	unsigned int len;
	UTF *ptr;
};

typedef struct Window Window;

extern Window windowCreate();