#include "core/buffer/chars.h"

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
inline void charsDestroy(Chars *chars) {
	if (chars == nullptr) {
		return;
	}

	if (chars->next != nullptr) {
		chars->next->perv = chars->perv;
	}
	if (chars->perv != nullptr) {
		chars->perv->next = chars->next;
	}

	free(chars);
}
