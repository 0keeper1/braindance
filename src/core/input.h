#pragma once

#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <unistd.h>

#define ESC 27

typedef enum
{
	ENTER,
	ARROW_UP,
	FN_ARROW_UP,
	CTRL_ARROW_UP,
	ALT_ARROW_UP,
	SHIFT_ARROW_UP,
	SHIFT_CTRL_ARROW_UP,
	SHIFT_ALT_ARROW_UP,
	ARROW_DOWN,
	FN_ARROW_DOWN,
	CTRL_ARROW_DOWN,
	ALT_ARROW_DOWN,
	SHIFT_ARROW_DOWN,
	SHIFT_CTRL_ARROW_DOWN,
	SHIFT_ALT_ARROW_DOWN,
	ARROW_RIGHT,
	FN_ARROW_RIGHT,
	CTRL_ARROW_RIGHT,
	ALT_ARROW_RIGHT,
	SHIFT_ARROW_RIGHT,
	SHIFT_CTRL_ARROW_RIGHT,
	SHIFT_ALT_ARROW_RIGHT,
	ARROW_LEFT,
	FN_ARROW_LEFT,
	CTRL_ARROW_LEFT,
	ALT_ARROW_LEFT,
	SHIFT_ARROW_LEFT,
	SHIFT_CTRL_ARROW_LEFT,
	SHIFT_ALT_ARROW_LEFT,
	TIMEOUT,
} Buttons;

static char arr[][30] = {
    "ENTER",
    "ARROW_UP",
    "FN_ARROW_UP",
    "CTRL_ARROW_UP",
    "ALT_ARROW_UP",
    "SHIFT_ARROW_UP",
    "SHIFT_CTRL_ARROW_UP",
    "SHIFT_ALT_ARROW_UP",
    "ARROW_DOWN",
    "FN_ARROW_DOWN",
    "CTRL_ARROW_DOWN",
    "ALT_ARROW_DOWN",
    "SHIFT_ARROW_DOWN",
    "SHIFT_CTRL_ARROW_DOWN",
    "SHIFT_ALT_ARROW_DOWN",
    "ARROW_RIGHT",
    "FN_ARROW_RIGHT",
    "CTRL_ARROW_RIGHT",
    "ALT_ARROW_RIGHT",
    "SHIFT_ARROW_RIGHT",
    "SHIFT_CTRL_ARROW_RIGHT",
    "SHIFT_ALT_ARROW_RIGHT",
    "ARROW_LEFT",
    "FN_ARROW_LEFT",
    "CTRL_ARROW_LEFT",
    "ALT_ARROW_LEFT",
    "SHIFT_ARROW_LEFT",
    "SHIFT_CTRL_ARROW_LEFT",
    "SHIFT_ALT_ARROW_LEFT",
    "TIMEOUT",
};

typedef struct
{
	union
	{
		unsigned char character;
		Buttons button;
	};
	bool isbtn;
	bool isctrl;
	bool isalt;
	bool isfn;
} Key;

extern const Key *const keyRead();
