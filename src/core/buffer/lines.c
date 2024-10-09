#include "./lines.h"


Lines *linesCreate() {
	Lines *lines_ptr = malloc(sizeof(Lines));
	if (lines_ptr == nullptr) {
		return nullptr;
	}
	lines_ptr->cap = 0;
	lines_ptr->len = 0;
	lines_ptr->next = nullptr;
	lines_ptr->next = nullptr;
	lines_ptr->end_ptr = nullptr;
	lines_ptr->start_ptr = nullptr;
	return lines_ptr;
}

void linesDestroy(Lines *line_ptr) {
	line_ptr->start_ptr = nullptr;
	line_ptr->end_ptr = nullptr;
	line_ptr->cap = 0;
	line_ptr->len = 0;
}

Chars *linesGetCharsByIndex(const Lines *lines_ptr, const size_t index) {
	if (lines_ptr == nullptr) {
		return nullptr;
	}

	if (index > lines_ptr->len) {
		return nullptr;
	}

	if (index > lines_ptr->len / 2) {
		const Chars *chars_ptr = lines_ptr->end_ptr;
		for (size_t ctr = 0; chars_ptr != nullptr; chars_ptr = chars_ptr->perv, ctr++) {
			// TODO count from end if linked list
		}
	} else if (index < lines_ptr->len / 2) {
		const Chars *chars_ptr = lines_ptr->start_ptr;
		for (size_t ctr = 0; chars_ptr != nullptr; chars_ptr = chars_ptr->next, ctr++) {
			// TODO count from
		}
	}


	return nullptr;
}

