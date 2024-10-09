#pragma once

#include <stddef.h>

#include "lines.h"

typedef struct Content {
    Lines *start_ptr;
    size_t len;
    Lines *end_ptr;
} Content;

extern Content *contentCreate();

extern void contentNewLine(Content *const content_ptr);

extern void contentReadFromFile(Content *const content_ptr, const char *const file_path);

extern void contentWriteToFile(Content *const content_ptr, const char *const file_path);
