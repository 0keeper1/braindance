#pragma once

#include "../macros.h"
#include "./core/input.h"

#define MOD_CTRL 0b00000010
#define MOD_ALT 0b00000100
#define MOD_FN 0b00001000

BIND(EXIT, 'q', MOD_CTRL, 1)

BIND(SWITCH_LAYOUT, 'x', MOD_CTRL, 1)
BIND(SWITCH_LAYOUT_TO_EDITOR, 'e', MOD_CTRL, 2)
BIND(SWITCH_LAYOUT_TO_PROMPT, 'p', MOD_CTRL, 2)

extern Result keyactionSWITCH_LAYOUT(Core *const coreptr);
extern Result keyactionSWITCH_LAYOUT_TO_PROMPT(Core *const coreptr);
extern Result keyactionSWITCH_LAYOUT_TO_EDITOR(Core *const coreptr);
extern Result keyactionEXIT(Core *const coreptr);