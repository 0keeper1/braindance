#include "error.h"

#include <assert.h>

int divide(const int x, const int y, ERR)
{
	if (x == 0 || y == 0)
	{
		SET_ERROR(FAILED, "divide by zero");
		return 0;
	}
	UNSET;
	return x / y;
}

void testError()
{
	ERROR;

	divide(1, 3, &error);
	assert(error.code == NOTSET);
	assert(error.msg.ptr == nullptr);
	assert(error.msg.len == 0);
	assert(error.msg.cap == 0);

	divide(4, 0, &error);
	constexpr char msg_clone[] = "divide by zero";
	assert(error.code == FAILED);
	assert(strncmp(error.msg.ptr, msg_clone, strlen(msg_clone)) == 0);
	assert(error.msg.len == strlen(msg_clone));
	assert(error.msg.cap == strlen(msg_clone));

	FE_ERROR;
}

int multiError(const int x, const int y, ERR)
{
	if (x == 0)
	{
		SET_ERROR(FAILED, "divide by zero x cannot be zero");
		return 0;
	}
	if (y == 0)
	{
		SET_ERROR(FAILED, "divide by zero y cannot be zero");
		return 0;
	}

	UNSET;
	return x / y;
}

void testMultiSetError()
{
	ERROR;
	constexpr char msg_clone[] = "divide by zero x cannot be zero";

	int res = multiError(4, 0, &error);
	res		= multiError(0, 0, &error);
	assert(res == 0);
	assert(error.code == FAILED);
	assert(strncmp(error.msg.ptr, msg_clone, strlen(msg_clone)) == 0);

	FE_ERROR;
}

int main()
{
	testError();
	testMultiSetError();
	return 0;
}