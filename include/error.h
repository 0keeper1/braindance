#pragma once

#include "macros.h"
#include <stdlib.h>
#include <string.h>

/**
 * @brief Error Codes
 */
typedef enum ErrorCode // : char
{
	NOTSET = 0,
	FAILED = 1,

	// global errors
	ERR_NULL_POINTER,

	// std errors
	STD_ERR_COPY_STRING_FAILED,
	STD_ERR_REALLOCATION_FAILED,

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

	// path errors
	PATH_ERR_INVALID_PATH,
} ErrorCode;

/**
 * @brief Global ERROR
 */
static struct
{
	ErrorCode code;
	STRING(message);
} ERROR = {NOTSET, .message = {.cap = 0, .len = 0, .ptr = nullptr}};

/**
 * @brief Set ERROR code
 * @param error_code ERROR code ErrorCode
 */
#define SET_ERROR_CODE(error_code) ERROR.code = error_code;

/**
 * @brief Set ERROR message
 * @param msg Message that will set to Global ERROR
 */
#define SET_ERROR_MESSAGE(msg)                                                 \
	{                                                                          \
		const size_t len = strlen(msg);                                        \
		if (len)                                                               \
		{                                                                      \
			if (len > ERROR.message.cap)                                       \
			{                                                                  \
				char* new_ptr;                                                 \
				if ((new_ptr = (char*) realloc(ERROR.message.ptr,              \
											   ERROR.message.cap + len)) ==    \
					nullptr)                                                   \
				{                                                              \
					ERROR.code = ERR_NULL_POINTER;                             \
					if (ERROR.message.ptr != nullptr)                          \
					{                                                          \
						free(ERROR.message.ptr);                               \
					}                                                          \
					ERROR.message.len = 0, ERROR.message.cap = 0;              \
					ERROR.code = STD_ERR_REALLOCATION_FAILED;                  \
				}                                                              \
				else                                                           \
				{                                                              \
					ERROR.message.ptr = new_ptr;                               \
					ERROR.message.cap += len, ERROR.message.len = len;         \
					if (strncpy(ERROR.message.ptr, msg, len) == nullptr)       \
					{                                                          \
						ERROR.code = STD_ERR_COPY_STRING_FAILED;               \
					}                                                          \
				}                                                              \
			}                                                                  \
			else                                                               \
			{                                                                  \
				ERROR.message.len = len;                                       \
				if (strncpy(ERROR.message.ptr, msg, len) == nullptr)           \
				{                                                              \
					ERROR.code = STD_ERR_COPY_STRING_FAILED;                   \
				}                                                              \
			}                                                                  \
		}                                                                      \
	}

const char* getErrorMessage(ErrorCode code);