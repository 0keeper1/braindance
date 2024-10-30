#include <core/buffer/chars.h>

#include "nanotest/lib.h"

NANO_FUNCTION(test_chars, true, {
	Chars *char1_ptr = charsCreate('h');
	Chars *char2_ptr = charsCreate('e');
	Chars *char3_ptr = charsCreate('l');
	Chars *char4_ptr = charsCreate('l');
	Chars *char5_ptr = charsCreate('o');

	char1_ptr->next = char2_ptr;
	char2_ptr->next = char3_ptr;
	char3_ptr->next = char4_ptr;
	char4_ptr->next = char5_ptr;

	char5_ptr->perv = char4_ptr;
	char4_ptr->perv = char3_ptr;
	char3_ptr->perv = char2_ptr;
	char2_ptr->perv = char1_ptr;

	charsDestroy(char3_ptr);
})
