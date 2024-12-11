#pragma once

union Data
{
	char chr;
	char esc[9];
};

typedef struct Char
{
	struct Char* prev;
	union
	{
		char chr;
		char esc[9];
	};
	bool is_escape;
	struct Char* next;
} Char;

/**
 * @brief Allocate Char on Heap
 * @throw STD_ERR_REQUEST_FOR_MEMORY_FAILED Out Of Mem
 * @return Allocated Char on heap
 */
Char* charNew();

/**
 * @brief Set content to char struct
 * @throw CHAR_ERR_ONLY_ESC_ALLOWED cant set Data to character when is_escape is true
 * @throw CHAR_ERR_ESC_NOT_ALLOWED cant set Data to Escape code when is_escape is false
 * @return if set the content failed return nullptr else return self
 */
Char* charSet(Char* self,
			  union Data data,
			  bool is_escape,
			  const Char* prev,
			  const Char* next);
