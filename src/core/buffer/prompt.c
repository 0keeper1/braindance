#include "prompt.h"

#include <stdio.h>

#include "../errors.h"
#include <stdlib.h>

Prompt promptCreate() {
    const Prompt prompt = {.len = 0, .ptr = NULL, .cap = 0};
    return prompt;
}

Result promptAppend(Prompt *const promptptr, const char character) {
    if (promptptr->cap == 0 || promptptr->len + 1 >= promptptr->cap) {
        promptptr->ptr = realloc(promptptr->ptr, promptptr->cap + 5);
        if (promptptr->ptr == NULL) {
            return OUT_OF_MEMORY;
        }
        promptptr->cap += 5;
    }
    if (promptptr->len == 0) {
        promptptr->ptr[0] = character;
    } else {
        promptptr->ptr[promptptr->len + 1] = character;
    }
    promptptr->len += 1;

    return SUCCESSFUL;
}

Result promptExecute() {
}

void promptFree(const Prompt *const promptptr) {
    free(promptptr->ptr);
}

