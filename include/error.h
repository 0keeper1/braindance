#pragma once

#include "macros.h"

/**
 * @brief Error Codes
 */
typedef enum ErrorCode : char
{
	NOTSET,
	FAILED,

	// global errors
	ERR_NULL_POINTER,

	// std errors
	STD_ERR_COPY_STRING_FAILED,
	STD_ERR_REALLOCATION_FAILED,
	STD_ERR_REQUEST_FOR_MEMORY_FAILED,

	// command line errors
	CLI_ERR_INVALID_COMMAND,
	CLI_ERR_MISSING_ARGUMENT,
	CLI_ERR_TOO_MANY_ARGUMENTS,
	CLI_ERR_COMMAND_NOT_FOUND,
	CLI_ERR_INVALID_PATH,

	// file errors
	FILE_ERR_OPEN_FAILED,
	FILE_ERR_PARSE_CTX_FAILED,
	FILE_ERR_FILE_NOT_FOUND,
	FILE_ERR_SEEK_FAILED,

	// path errors
	PATH_ERR_INVALID_PATH,

	// Char errors
	CHAR_ERR_ONLY_ESC_ALLOWED,
	CHAR_ERR_ESC_NOT_ALLOWED,
} ErrorCode;

/**
 * @brief Global ERROR
 */
struct Error
{
	ErrorCode code;
	STRING(message);
};

extern struct Error Error;

extern const char* getErrorMessage(ErrorCode code);
