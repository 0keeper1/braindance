#pragma once

#include "errors.h"
#include "./buffer/chars.h"

enum UnionType {
    UT_Chars,
    UT_String,
};

typedef struct Prompt {
    size_t len;

    union {
        Chars *chars;
        char *string;
    };

    enum UnionType mode;
    size_t cap;
} Prompt;

extern Prompt promptCreate();

extern Result promptAppend(Prompt *const promptptr, const char character);

extern Result promptDeleteEnd(Prompt *const promptptr);

extern Result promptToChars(Prompt *const promptptr);

extern void promptFree(const Prompt *const promptptr);

