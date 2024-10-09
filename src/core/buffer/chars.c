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

void charsDestroy(Chars *chars) {
	if (chars == nullptr) {
		return;
	}
	Chars *tmp_next_ptr = chars->next;
	tmp_next_ptr->perv = chars->perv;
	chars->perv->next = tmp_next_ptr;
	free(chars);
}
