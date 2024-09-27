#include "./chars.h"

[[gnu::always_inline]]
inline Chars *charsCreate(const char chr) {
	Chars *ptr = calloc(1, sizeof(Chars));
	ptr->perv = nullptr;
	ptr->chr = chr;
	ptr->next = nullptr;
	return ptr;
}

[[gnu::always_inline]]
inline void charsFree(Chars *chrptr) { free(chrptr); }

void charsRemoveChar(Chars *const chrptr) {
	Chars *tmpperv = chrptr->perv;
	Chars *tmpnext = chrptr->next;
	if (tmpnext != nullptr) {
		tmpnext->perv = tmpperv;
	}
	if (tmpperv != nullptr) {
		tmpperv->next = tmpnext;
	}
	charsFree(chrptr);
}

void charsInsertChar(Chars *const chrptr, const char newchar) {
	Chars *newcharsptr = charsCreate(newchar);
	newcharsptr->perv = chrptr;
	newcharsptr->next = chrptr->next;
	chrptr->next = newcharsptr;
}

Chars *charsConvertStringToChars(const char *ptr, const unsigned int len) {
	Chars *charsptr, *pervcharptr = nullptr;
	Chars *const firstcharptr = charsptr = charsCreate('\0');
	for (int i = 0; i < len; ++i) {
		charsptr->chr = ptr[i];
		pervcharptr = charsptr;
		charsptr = charsCreate('\0');
		charsptr->perv = pervcharptr;
		pervcharptr->next = charsptr;
	}
	return firstcharptr;
}
