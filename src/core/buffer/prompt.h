#pragma once

#include <stddef.h>

#include "./buffer/chars.h"

typedef struct Prompt {
    Chars *start_ptr;
    size_t len;
    Chars *end_ptr;
} Prompt;

extern Prompt promptCreate();
