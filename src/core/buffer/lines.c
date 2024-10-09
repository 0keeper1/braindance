#include "./lines.h"

#include <stdlib.h>

Lines *linesCreate() {
	Lines *lines_ptr = malloc(sizeof(Lines));
	if (lines_ptr == nullptr) {
		return nullptr;
	}
	lines_ptr->len = 0;
	lines_ptr->next = nullptr;
	lines_ptr->end_ptr = nullptr;
	lines_ptr->start_ptr = nullptr;
	return lines_ptr;
}

void linesDestroy(Lines *line_ptr) {
	line_ptr->start_ptr = nullptr;
	line_ptr->end_ptr = nullptr;
	line_ptr->len = 0;
}

Chars *linesGetCharsByIndex(const Lines *lines_ptr, const size_t index) {
	if (lines_ptr == nullptr) {
		return nullptr;
	}

	if (index > lines_ptr->len) {
		return nullptr;
	}
	// TODO check index if index is 0 insert to start_ptr->perv and if index is lines_ptr->len insert to end_ptr->next
	if (index > lines_ptr->len / 2) {
		Chars *chars_ptr = lines_ptr->end_ptr;
		for (size_t ctr = lines_ptr->len; chars_ptr != nullptr, ctr - 1 != -1; chars_ptr = chars_ptr->perv, ctr--) {
			if (ctr == index) {
				return chars_ptr;
			}
		}
	} else if (index < lines_ptr->len / 2) {
		Chars *chars_ptr = lines_ptr->start_ptr;
		for (size_t ctr = 0; chars_ptr != nullptr, ctr <= lines_ptr->len, ctr < lines_ptr->len;
		     chars_ptr = chars_ptr->next, ctr++) {
			if (ctr == index) {
				return chars_ptr;
			}
		}
	}
	return nullptr;
}


void linesInsertChars(Lines *lines_ptr, const size_t index, const char chr) {
	if (lines_ptr == nullptr) {
		return;
	}

	if (index > lines_ptr->len) {
		return;
	}

	Chars *new_chars_ptr = charsCreate(chr);
	if (new_chars_ptr == nullptr) {
		return;
	}

	Chars *chars_ptr = linesGetCharsByIndex(lines_ptr, index);
	if (chars_ptr == nullptr) {
		return;
	}

	new_chars_ptr->next = chars_ptr->next;
	chars_ptr->next->perv = new_chars_ptr;
	lines_ptr->len++;

	if (index == lines_ptr->len) {
		lines_ptr->end_ptr = new_chars_ptr;
	} else if (index == 0) {
		lines_ptr->start_ptr = new_chars_ptr;
	}
}

void linesDeleteChars(Lines *lines_ptr, const size_t index) {
	if (lines_ptr == nullptr) {
		return;
	}

	if (index > lines_ptr->len) {
		return;
	}

	Chars *chars_ptr = linesGetCharsByIndex(lines_ptr, index);
	if (chars_ptr == nullptr) {
		return;
	}

	if (index == 0) {
		lines_ptr->start_ptr = chars_ptr->next;
	} else if (index == lines_ptr->len) {
		lines_ptr->end_ptr = chars_ptr->perv;
	}

	charsDestroy(chars_ptr);
}
