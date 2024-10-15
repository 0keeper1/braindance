#include "content.h"

#include <stdio.h>

Content *contentCreate() {
    static Content content; // static because of the editor open single file at time

    content.start_ptr = linesCreate();
    content.len = 1;
    content.end_ptr = content.start_ptr;

    return &content;
}

void contentNewLine(Content *const content_ptr) {
    if ((content_ptr->end_ptr->next = linesCreate()) == nullptr) {
        return;
    }
    content_ptr->len++;
    (content_ptr->end_ptr->next)->perv = content_ptr->end_ptr;
    content_ptr->end_ptr = content_ptr->end_ptr->next;
}

void contentReadFromFile(Content *const content_ptr, const char *const file_path) {
    FILE *file_ptr = fopen(file_path, "r");
    if (file_ptr == nullptr) {
        return;
    }

    int chr = '\0';

    while ((chr = fgetc(file_ptr)) != EOF) {
        if (chr == '\n') {
            contentNewLine(content_ptr);
        }
        linesAppend(content_ptr->end_ptr, (char) chr);
    }
    fclose(file_ptr);
}

void contentWriteToFile(const Content *const content_ptr, const char *const file_path) {
    FILE *file_ptr = fopen(file_path, "w");
    if (file_ptr == nullptr) {
        return;
    }

    for (const Lines *tmp_lines_ptr = content_ptr->start_ptr; tmp_lines_ptr != nullptr;
         tmp_lines_ptr = tmp_lines_ptr->next) {
        for (const Chars *tmp_chars_ptr = tmp_lines_ptr->start_ptr; tmp_chars_ptr->chr != '\0';
             tmp_chars_ptr = tmp_chars_ptr->next) {
            fputc(tmp_chars_ptr->chr, file_ptr);
        }
    }
    fclose(file_ptr);
}
