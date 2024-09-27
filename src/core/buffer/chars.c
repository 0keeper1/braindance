#include "./chars.h"

#include <stdlib.h>

[[gnu::always_inline]]
inline Chars *charsCreate(const char chr) {
	Chars *ptr = malloc(sizeof(Chars));
	if (ptr == nullptr) {
		return nullptr;
	}
	ptr->perv = nullptr;
	ptr->chr = chr;
	ptr->next = nullptr;
	return ptr;
}

[[gnu::always_inline]]
inline void charsFree(Chars *const chars_ptr) {
	free(chars_ptr);
}

Result charsRemoveAt(Chars *const chars_ptr) {
	if (chars_ptr == nullptr) {
		return FAILED;
	}

	Chars *tmp_perv = chars_ptr->perv;
	Chars *tmp_next = chars_ptr->next;

	if (tmp_next != nullptr) {
		tmp_next->perv = tmp_perv;
	}

	if (tmp_perv != nullptr) {
		tmp_perv->next = tmp_next;
	}

	charsFree(chars_ptr);

	return SUCCESSFUL;
}

Result charsRemove(Chars *chars_ptr) {
	if (chars_ptr == nullptr) {
		return FAILED;
	}

	for (; chars_ptr->next != nullptr; chars_ptr = chars_ptr->next) {
	}

	charsRemoveAt(chars_ptr);

	return SUCCESSFUL;
}

Result charsAppend(Chars *chars_ptr, const char chr) {
	if (chars_ptr == nullptr) {
		return FAILED;
	}

	for (; chars_ptr->next != nullptr; chars_ptr = chars_ptr->next) {
	}

	Chars *n_chars_ptr = charsCreate(chr);

	if (n_chars_ptr == nullptr) {
		return FAILED;
	}

	chars_ptr->next = n_chars_ptr;
	n_chars_ptr->chr = chr;
	n_chars_ptr->perv = chars_ptr;

	return SUCCESSFUL;
}

Result charsInsertAt(Chars *const chars_ptr, const char new_chr) {
	if (chars_ptr == nullptr) {
		return FAILED;
	}

	Chars *n_chars_ptr = charsCreate(new_chr);

	if (n_chars_ptr == nullptr) {
		return FAILED;
	}

	n_chars_ptr->perv = chars_ptr;
	n_chars_ptr->next = chars_ptr->next;
	chars_ptr->next = n_chars_ptr;

	return SUCCESSFUL;
}

size_t charsLength(const Chars *chars_ptr) {
	if (chars_ptr == nullptr) {
		return 0;
	}

	size_t len = 0;
	for (; chars_ptr != nullptr; chars_ptr = chars_ptr->next) {
		len++;
	}

	return len;
}

Chars *charsGetEndPtr(Chars *chars_ptr) {
	if (chars_ptr == nullptr) {
		return nullptr;
	}

	for (; chars_ptr != nullptr; chars_ptr = chars_ptr->next) {
	}

	return chars_ptr;
}

String *charsConvertCharsToString(const Chars *chars_ptr) {
	if (chars_ptr == nullptr) {
		return nullptr;
	}

	String *string_ptr = stringCreate();

	for (; chars_ptr->next != nullptr; chars_ptr = chars_ptr->next) {
		if (stringAppend(string_ptr, chars_ptr->chr) != SUCCESSFUL) {
			return nullptr;
		}
	}

	return string_ptr;
}

Chars *charsConvertStringToChars(const String *string_ptr) {
	if (string_ptr == nullptr) {
		return nullptr;
	}

	Chars *chars_ptr = nullptr, *perv_chars_ptr = nullptr;
	Chars *const first_chars_ptr = chars_ptr = charsCreate('\0');

	if (first_chars_ptr == nullptr) {
		return nullptr;
	}

	for (size_t c = 0; c < string_ptr->len; ++c) {
		chars_ptr->chr = string_ptr->ptr[c];
		perv_chars_ptr = chars_ptr;
		chars_ptr = charsCreate('\0');
		chars_ptr->perv = perv_chars_ptr;
		perv_chars_ptr->next = chars_ptr;
	}

	return first_chars_ptr;
}
