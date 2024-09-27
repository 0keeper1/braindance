#include "prompt.h"
#include "../errors.h"
#include "./buffer/chars.h"

#include <stdio.h>
#include <stdlib.h>

[[gnu::always_inline]]
inline Prompt promptCreate() {
    const Prompt prompt = {.len = 0, .string = nullptr, .cap = 0, .mode = UT_String};
    return prompt;
}

Result promptAppend(Prompt *const promptptr, const char character) {
    // TODO check if Chars append to chars if String append to string.
    if (promptptr->cap == 0 || promptptr->len + 1 >= promptptr->cap) {
        promptptr->string = realloc(promptptr->string, promptptr->cap + 5);
        if (promptptr->string == nullptr) {
            return FAILED;
        }
        promptptr->cap += 5;
    }

    if (promptptr->len == 0) {
        promptptr->string[0] = character;
    } else {
        promptptr->string[promptptr->len + 1] = character;
    }

    promptptr->len += 1;

    return SUCCESSFUL;
}

Result promptDeleteEnd(Prompt *const promptptr) {
    if (promptptr->len == 0) {
        return SUCCESSFUL;
    }

    if (promptptr->mode == UT_String) {
        promptptr->string[promptptr->len] = '\0';
        promptptr->len -= 1;
        return SUCCESSFUL;
    }

    // TODO: add chars delete
    return SUCCESSFUL;
}

Result promptToChars(Prompt *const promptptr) {
    if (promptptr->mode == UT_Chars) {
        return SUCCESSFUL;
    }

    if ((promptptr->chars = charsConvertStringToChars(promptptr->string, promptptr->len)) == nullptr) {
        return FAILED;
    }
    promptptr->mode = UT_Chars;

    return SUCCESSFUL;
}

Result prmptToString(Prompt *const promptptr) {
    if (promptptr->mode == UT_String) {
        return SUCCESSFUL;
    }

    // TODO: charsConvertCharsToString(promptptr->string, promptptr->len)
    promptptr->mode = UT_String;
    return SUCCESSFUL;
}

Result promptExecute() {
}

[[gnu::always_inline]]
inline void promptFree(const Prompt *const promptptr) {
    if (promptptr->mode == UT_String) {
        return;
    }
    free(promptptr->string);
}

