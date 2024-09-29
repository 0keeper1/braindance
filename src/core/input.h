#pragma once

#include "../errors.h"
#include "../settings.h"
#include "./core.h"
#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <str.h>
#include <unistd.h>

typedef enum {
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

enum Mod {
	NOMOD = 0b00000000, // 0
	BTN = 0b00000001, // 1
	CTRL = 0b00000010, // 2
	ALT = 0b00000100, // 4
	FN = 0b00001000, // 8
	CHAR = 0b00010000, // 16
	TIMEOUT = 0b10000000, // 32
};

typedef struct {
	union {
		unsigned char character;
		Buttons button;
	};

	unsigned int mod: 8;
} Key;

struct Keybind {
	unsigned char character;
	unsigned int modifier: 8;
	unsigned char repeat;
};

typedef struct {
	Key key;
	unsigned int keycounter;
	bool commit;
} _KeyQueue;

static _KeyQueue KeyQueue;

extern Result keyProcess(Core *const coreptr);

extern const Key *keyRead();

extern Result keyQueueHandler();

extern void keyQueueZero();

extern Result keyExec(Core *const coreptr);

extern bool checkIsTimeOut();

extern bool checkKeyWithBinding(const struct Keybind *const keybind);

extern bool checkIsInputKey();

extern Result writeToLayout(Core *const coreptr);

extern bool checkKeyIsBackSpace();
