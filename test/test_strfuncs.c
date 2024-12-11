#include "error.h"
#include "macros.h"
#include "utils/strfuncs.h"

#include <assert.h>

void testStrSetCapacity()
{
	STRING(my_str);

	my_str.ptr = calloc(10, sizeof(char));
	my_str.len = 9;
	my_str.cap = 10;
	memcpy(my_str.ptr, "ABCDEFGHI", sizeof(char) * my_str.len);

	strSetCapacity(&my_str, 40);
	assert(Error.code == NOTSET);
	assert(my_str.len == 9);
	assert(my_str.cap == 40);
	assert(strncmp(my_str.ptr, "ABCDEFGHI", 9) == 0);

	strSetCapacity(&my_str, 3);
	assert(Error.code == NOTSET);
	assert(my_str.len == 3);
	assert(my_str.cap == 3);
	assert(strncmp(my_str.ptr, "ABCDEFGHI", 3) == 0);
}

int main()
{
	testStrSetCapacity();
}