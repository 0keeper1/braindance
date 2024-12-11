#include "error.h"
#include <buffers/chars.h>

Char* charNew()
{
	const auto self = (Char*) calloc(1, sizeof(Char));
	if (self == nullptr)
	{
		SET_ERROR_CODE(STD_ERR_REQUEST_FOR_MEMORY_FAILED);
		return nullptr;
	}

	return self;
}

Char* charSet(Char* self,
			  const union Data data,
			  const bool is_escape,
			  const Char* prev,
			  const Char* next)
{
	if (self == nullptr)
	{
		SET_ERROR_CODE(ERR_NULL_POINTER);
		return nullptr;
	}

	self->is_escape = is_escape;

	if (prev != nullptr)
	{
		SET_CHAR_PERV(self, prev);
	}

	if (next != nullptr)
	{
		SET_CHAR_NEXT(self, next);
	}

	if (is_escape)
	{
		if (data.esc[0] != 27)
		{
			SET_ERROR_CODE(CHAR_ERR_ONLY_ESC_ALLOWED);
			return nullptr;
		}
		memmove(self->esc, data.esc, sizeof(char) * 8);
	}
	else
	{
		if (data.esc[0] == 27)
		{
			SET_ERROR_CODE(CHAR_ERR_ESC_NOT_ALLOWED);
			return nullptr;
		}
		self->chr = data.chr;
	}

	return self;
}
