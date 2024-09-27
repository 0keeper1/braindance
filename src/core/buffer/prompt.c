#include "prompt.h"
#include "../errors.h"
#include "./str.h"
#include "./buffer/chars.h"

#include <stdlib.h>

[[gnu::always_inline]]
inline Prompt promptCreate() {
    const Prompt prompt = {.len = 0, .start_ptr = nullptr, .end_ptr = nullptr, .cap = 0};
    return prompt;
}

Result promptAppend(Prompt *const prompt_ptr, const char character) {
    if (prompt_ptr == nullptr) {
        return FAILED;
    }

    if (prompt_ptr->start_ptr == nullptr && prompt_ptr->end_ptr == nullptr) {
        prompt_ptr->start_ptr = charsCreate(character);
        prompt_ptr->end_ptr = prompt_ptr->start_ptr;
        prompt_ptr->len += 1;
        prompt_ptr->cap += 1;
        return SUCCESSFUL;
    }

    if (charsAppend(prompt_ptr->end_ptr, character) != SUCCESSFUL) {
        return FAILED;
    }
    prompt_ptr->end_ptr = prompt_ptr->end_ptr->next;
    prompt_ptr->len += 1;
    prompt_ptr->cap += 1;

    return SUCCESSFUL;
}

Result promptDeleteEnd(Prompt *const prompt_ptr) {
    if (prompt_ptr == nullptr) {
        return FAILED;
    }

    if (prompt_ptr->end_ptr == nullptr) {
        if (prompt_ptr->start_ptr == nullptr) {
            return FAILED;
        }

        prompt_ptr->end_ptr = charsGetEndPtr(prompt_ptr->start_ptr);
    }

    if (prompt_ptr->len - 1 == 0) {
        charsFree(prompt_ptr->end_ptr);
        prompt_ptr->len = 0;
        prompt_ptr->start_ptr = nullptr;
        prompt_ptr->end_ptr = nullptr;
        prompt_ptr->cap = 0;
        return SUCCESSFUL;
    }

    Chars *tmp_chars_ptr = prompt_ptr->end_ptr->perv;
    charsRemoveAt(prompt_ptr->end_ptr);
    prompt_ptr->end_ptr = tmp_chars_ptr;
    prompt_ptr->len -= 1;
    prompt_ptr->cap -= 1;

    return SUCCESSFUL;
}

char *promptAsString(const Prompt *const prompt_ptr) {
    if (prompt_ptr == nullptr) {
        return nullptr;
    }
    String *string_ptr = charsConvertCharsToString(prompt_ptr->start_ptr);


    if (string_ptr == nullptr) {
        return nullptr;
    }
    char *char_ptr = string_ptr->ptr;

    stringFree(string_ptr);

    return char_ptr;
}

[[gnu::always_inline]]
inline void promptFree(Prompt *const promptptr) {
    // TODO
    // charsFree(promptptr->start_ptr);
    // promptptr->cap = 0;
    // promptptr->start_ptr = nullptr;
    // promptptr->end_ptr = nullptr;
    // promptptr->len = 0;
}

