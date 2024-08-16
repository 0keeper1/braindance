#pragma once

#include "../buffer/windowbuf.h"
#include "../offset.h"
#include "../core.h"
#include "../../errors.h"
#include "./layouts.h"
#include <stdio.h>

#define SCREEN_CLEAR "\x1b[2J"

#define BUFFER_CLEAR "\x1b[3J"

#define CURSOR_AT_START "\x1b[H"

#define HIDE_CURSOR "\x1b[?25l"

#define SHOW_CURSOR "\x1b[?25h"

extern Result display( Core *const coreptr);
