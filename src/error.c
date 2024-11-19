#include "error.h"

struct Error Error = {NOTSET, .message = {.cap = 0, .len = 0, .ptr = nullptr}};

const char* getErrorMessage(const enum ErrorCode code)
{
	switch (code)
	{
		// TODO implement
		default:
			return "Unknown Error";
	}
}
