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

extern Result promptAppend(Prompt *const promptptr, const char character);

extern Result promptDeleteEnd(Prompt *const promptptr);

void promptFree(const Prompt *const promptptr);

