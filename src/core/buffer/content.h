#pragma once

#include "lines.h"

typedef struct Content {
    long lines_count;
    Lines *start_ptr;
    Lines *end_ptr;
} Content;

extern Content *contentCreate();

extern void contentNewLine(Content *const content_ptr);

extern void contentReadFromFile(Content *const content_ptr, const char *const file_path);

extern void contentWriteToFile(Content *const content_ptr, const char *const file_path);
