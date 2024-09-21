#pragma once

#include "errors.h"
#include "./buffer/chars.h"

enum UnionType {
    UM_Chars,
    UM_String,
};

typedef struct Prompt {
    unsigned int len;

    union {
        Chars *chars;
        char *ptr;
    };

    enum UnionType mode;
    unsigned int cap;
} Prompt;

Prompt promptCreate();

Result promptAppend(Prompt *const promptptr, const char character);

void promptFree(const Prompt *const promptptr);

