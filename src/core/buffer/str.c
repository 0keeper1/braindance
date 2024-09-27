#include "str.h"

#include <stdlib.h>

String *stringCreate() {
    String *string_ptr = malloc(sizeof(String));
    if (string_ptr == nullptr) {
        return nullptr;
    }
    string_ptr->cap = 5;
    string_ptr->ptr = malloc(5 * sizeof(char));
    string_ptr->len = 0;
    return string_ptr;
}

Result stringAppend(String *string_ptr, const char chr) {
    if (string_ptr == nullptr) {
        return FAILED;
    }

    if (string_ptr->cap < string_ptr->len + 1) {
        string_ptr->ptr = realloc(string_ptr->ptr, string_ptr->cap + 10); // TODO fix
        string_ptr->cap += 10;
    }

    string_ptr->ptr[string_ptr->len] = chr;
    string_ptr->len += 1;

    return SUCCESSFUL;
}

String *stringToString(char *const ptr, const size_t len, const size_t cap) {
    String *string_ptr = malloc(sizeof(String));
    if (string_ptr == nullptr) {
        return nullptr;
    }
    string_ptr->cap = cap;
    string_ptr->ptr = ptr;
    string_ptr->len = len;
    return string_ptr;
}

void stringFree(String *string_ptr) {
}
