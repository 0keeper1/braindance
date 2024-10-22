#pragma once

#define BIND( FUNCTIONALITY, CHARACTER, MOD, REPEAT )                                                                  \
const struct Keybind FUNCTIONALITY = { .character = CHARACTER, .modifier = MOD, .repeat = REPEAT };
