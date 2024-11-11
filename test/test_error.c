#include "error.h"

#include <assert.h>

int divide(const int x, const int y)
{
	if (x == 0 || y == 0)
	{
		SET_ERROR_CODE(FAILED);
		return 0;
	}
	return x / y;
}

void testError()
{
	divide(1, 3);
	assert(ERROR.code == NOTSET);
	assert(ERROR.message.ptr == nullptr);
	assert(ERROR.message.len == 0);
	assert(ERROR.message.cap == 0);

	divide(4, 0);
	assert(ERROR.code == FAILED);
}

int multiError(const int x, const int y)
{
	if (x == 0)
	{
		SET_ERROR_CODE(FAILED);
		return 0;
	}
	if (y == 0)
	{
		SET_ERROR_CODE(FAILED);
		return 0;
	}

	return x / y;
}

void testSetErrorMessageMacro()
{
	const char* message = "Zero Division\0";
	const size_t len	= strlen(message);

	SET_ERROR_CODE(ERR_NULL_POINTER);
	SET_ERROR_MESSAGE(message);

	assert(strncmp(ERROR.message.ptr, message, len) == 0);
	assert(ERROR.message.len == len);
}

void testMultiSetError()
{
	int res = multiError(4, 0);
	assert(res == 0);
	assert(ERROR.code == FAILED);

	res = multiError(0, 0);
	assert(res == 0);
	assert(ERROR.code == FAILED);
}

int main()
{
	testError();
	testMultiSetError();
	testSetErrorMessageMacro();

	return 0;
}