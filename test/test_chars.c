#include "buffers/chars.h"
#include "error.h"
#include "macros.h"

#include <assert.h>
#include <stdio.h>

void test_new_chars()
{
	const Char* chars = charNew();
	assert(chars != NULL);
	free(chars);
}

void test_set_chars()
{
	Char* chars = charNew();
	assert(chars != nullptr);

	union Data dt;
	dt.chr = 'A';

	const Char* set_char = charSet(chars, dt, false, nullptr, nullptr);
	assert(Error.code == NOTSET);
	assert(chars == set_char);
	assert(chars != nullptr);
	assert('A' == chars->chr);
	assert(chars->next == nullptr);
	assert(chars->prev == nullptr);
	RESET_ERROR;

	set_char = charSet(nullptr, dt, true, nullptr, nullptr);
	assert(Error.code == ERR_NULL_POINTER);
	assert(set_char == nullptr);
	RESET_ERROR;

	set_char = charSet(chars, dt, true, nullptr, nullptr);
	assert(Error.code == CHAR_ERR_ONLY_ESC_ALLOWED);
	assert(set_char == nullptr);
	RESET_ERROR;

	memset(&dt, 0, sizeof(dt));

	memmove(&dt, "\033[31;42m", sizeof(dt));

	set_char = charSet(chars, dt, false, nullptr, nullptr);
	assert(Error.code == CHAR_ERR_ESC_NOT_ALLOWED);
	assert(set_char == nullptr);
	RESET_ERROR;

	set_char = charSet(chars, dt, true, nullptr, nullptr);
	assert(Error.code == NOTSET);
	assert(set_char != nullptr);
	assert(strcmp(chars->esc, "\033[31;42m") == 0);
	RESET_ERROR;

	Char* n = charNew();
	Char* p = charNew();

	set_char = charSet(chars, dt, true, p, n);
	assert(Error.code == NOTSET);
	assert(strncmp(set_char->esc, "\033[31;42m", 8) == 0);
	assert(set_char->next == n);
	assert(set_char->prev == p);
	assert(set_char->is_escape);
	RESET_ERROR;

	free(n);
	free(p);
	free(chars);
}

int main()
{
	test_new_chars();
	test_set_chars();
	return 0;
}