#include "content.h"

Content *contentCreate() {
    static Content content; // static because of the editor open single file at time

    content.lines_count = 1;
    content.start_ptr = linesCreate();
    content.end_ptr = content.start_ptr;

    return &content;
}

void contentNewLine(Content *const content_ptr) {
    Lines *new_line = linesCreate();
    content_ptr->end_ptr->next = new_line;
    new_line->perv = content_ptr->end_ptr;
    content_ptr->end_ptr = new_line;
    content_ptr->end_ptr;
}

void contentReadFromFile(Content *const content_ptr, const char *const file_path) {
    // TODO
}

void contentWriteToFile(Content *const content_ptr, const char *const file_path) {
    // TODO
}

