#pragma once

#include "errors.h"

typedef struct Prompt {
    unsigned int len;
    char *ptr;
    unsigned int cap;
} Prompt;

Prompt promptCreate();

Result promptAppend(Prompt *const promptptr, const char character);

void promptFree(const Prompt *const promptptr);

