#pragma once

#include "./core/input.h"

#define MOD_CTRL 0b00000010
#define MOD_ALT 0b00000100
#define MOD_FN 0b00001000

#define BIND( FUNCTIONALITY, CHARACTER, MOD, REPEAT )                                                                  \
	const struct Keybind FUNCTIONALITY = { .character = CHARACTER, .modifier = MOD, .repeat = REPEAT };

/// DEFAULT KEYBINIDNGS DONT MISS THEM
BIND( EXIT, 'q', MOD_CTRL, 1 )

BIND(SWITCH_LAYOUT, 'x', MOD_CTRL, 1)
BIND(SWITCH_LAYOUT_TO_EDITOR, 'e', MOD_CTRL, 2)
BIND(SWITCH_LAYOUT_TO_PROMPT, 'p', MOD_CTRL, 2)
