#include "utils/strfuncs.h"

#include "error.h"
#include "macros.h"
#include "stdio.h"

typedef struct
{
	size_t cap;
	char* ptr;
	size_t len;
} str_t;

char* strFromFile(FILE* file, size_t* len, size_t* cap)
{
	if (file == nullptr || len == nullptr || cap == nullptr)
	{
		SET_ERROR_CODE(ERR_NULL_POINTER);
		return nullptr;
	}

	if (fseek(file, 0, SEEK_END) != 0)
	{
		SET_ERROR_CODE(FILE_ERR_SEEK_FAILED);
		return nullptr;
	}

	const size_t file_len = ftell(file) + 1;

	if (fseek(file, 0, SEEK_SET) != 0)
	{
		SET_ERROR_CODE(FILE_ERR_SEEK_FAILED);
		return nullptr;
	}

	char* contents = calloc(file_len, sizeof(char));
	if (contents == nullptr)
	{
		SET_ERROR_CODE(STD_ERR_REQUEST_FOR_MEMORY_FAILED);
		return nullptr;
	}

	*cap = file_len;
	*len = file_len;

	for (int chr = 0, c = 0; chr != EOF; chr = fgetc(file), c++)
	{
		contents[c] = (char) chr;
	}

	return contents;
}

void strSetCapacity(void* self, const size_t new_capacity)
{
	if (self == nullptr)
	{
		SET_ERROR_CODE(ERR_NULL_POINTER);
		return;
	}

	CAST(str_t, self);

	const char* new_ptr = realloc(str_t_self->ptr, new_capacity * sizeof(char));

	if (new_ptr == nullptr)
	{
		SET_ERROR_CODE(STD_ERR_REALLOCATION_FAILED);
		return;
	}

	if (new_ptr != str_t_self->ptr)
	{
		str_t_self->ptr = new_ptr;
	}

	if (str_t_self->len > new_capacity)
	{
		str_t_self->cap = new_capacity;
		str_t_self->len = new_capacity;
	}
	else
	{
		str_t_self->cap = new_capacity;
	}
}

void strFitCapacity(void* self)
{
	if (self == nullptr)
	{
		SET_ERROR_CODE(ERR_NULL_POINTER);
		return;
	}

	CAST(str_t, self);

	char* new_ptr = realloc(str_t_self->ptr, str_t_self->len * sizeof(char));
	if (new_ptr == nullptr)
	{
		SET_ERROR_CODE(STD_ERR_REALLOCATION_FAILED);
		return;
	}

	if (new_ptr != str_t_self->ptr)
	{
		str_t_self->ptr = new_ptr;
	}

	str_t_self->cap = str_t_self->len;
}

char* strCopy(void* self)
{
	if (self == nullptr)
	{
		SET_ERROR_CODE(ERR_NULL_POINTER);
		return nullptr;
	}

	CAST(str_t, self);

	char* new_ptr = calloc(str_t_self->len * sizeof(char), sizeof(char));
	if (new_ptr == nullptr)
	{
		SET_ERROR_CODE(STD_ERR_REQUEST_FOR_MEMORY_FAILED);
		return nullptr;
	}

	if (memccpy(new_ptr, str_t_self->ptr, '\0', str_t_self->len) == nullptr)
	{
		SET_ERROR_CODE(STD_ERR_COPY_STRING_FAILED);
		return nullptr;
	}

	return new_ptr;
}

void strDrop(void* self)
{
	if (self == nullptr)
	{
		SET_ERROR_CODE(ERR_NULL_POINTER);
		return;
	}

	CAST(str_t, self);

	free(str_t_self->ptr);
	str_t_self->ptr = nullptr;
	str_t_self->len = 0;
	str_t_self->cap = 0;
}

void strClear(void* self)
{
	if (self == nullptr)
	{
		SET_ERROR_CODE(ERR_NULL_POINTER);
		return;
	}

	CAST(str_t, self);

	memset(str_t_self->ptr, 0, str_t_self->cap);
	str_t_self->len = 0;
}
