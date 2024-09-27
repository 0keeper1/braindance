#pragma once

#include "errors.h"
#include "./buffer/chars.h"

typedef struct Prompt {
    size_t len;
    Chars *start_ptr;
    Chars *end_ptr;
    size_t cap;
} Prompt;

extern inline Prompt promptCreate();

extern Result promptAppend(Prompt *const prompt_ptr, const char character);

extern Result promptDeleteEnd(Prompt *const promptptr);

extern void promptFree(Prompt *const promptptr);

extern char *promptAsString(const Prompt *const prompt_ptr);
