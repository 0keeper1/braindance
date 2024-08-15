#pragma once

#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <unistd.h>

#define ESC 27

typedef enum : unsigned char
{
	ENTER,
	ARROW_UP,
	ARROW_DOWN,
	ARROW_RIGHT,
	ARROW_LEFT,
	TIMEOUT,
} Buttons;

typedef struct
{

	union
	{
		unsigned char character;
		Buttons button;
	};

	bool is_ctrl;
	bool is_alt;
	bool is_fn;
} Key;

extern const Key *const keyRead();
