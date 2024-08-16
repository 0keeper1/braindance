#pragma once

#include "../errors.h"
#include "../settings.h"
#include "./core.h"
#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

typedef enum
{
	ENTER,
	BACKSPACE,
	ESC,
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
	NONE,
} Buttons;

enum Mod
{
	NOMOD = 0b00000000,
	BTN = 0b00000001,
	CTRL = 0b00000010,
	ALT = 0b00000100,
	FN = 0b00001000,
	CHAR = 0b00010000,
	TIMEOUT = 0b10000000,
};

typedef struct
{
	union
	{
		unsigned char character;
		Buttons button;
	};
	unsigned int mod : 8;
} Key;

typedef struct
{
	Key key;
	unsigned int keycounter;
	bool commit;
} _KeyQueue;

static _KeyQueue KeyQueue;

extern Result keyProcess( Core *const coreptr );
extern const Key *const keyRead();
Result keyQueueHandler();
void keyQueueZero();