#pragma once

#include "macros.h"
#include <stdlib.h>
#include <string.h>

typedef enum ErrorCode : char
{
	NOTSET = 0, // NOTSET ERROR
	FAILED = 1, // UNKNOWN ERROR

	ERR_NULL_POINTER,

	CLI_ERR_INVALID_COMMAND,
	CLI_ERR_MISSING_ARGUMENT,
	CLI_ERR_TOO_MANY_ARGUMENTS,
	CLI_ERR_COMMAND_NOT_FOUND,
	CLI_ERR_INVALID_PATH,

	FILE_ERR_FILE_NOT_FOUND,
} ErrorCode;

typedef struct Error
{
	ErrorCode code;
	STRING(message);
} Error;

#define ERR Error* err

#define ERROR Error error = {NOTSET, {0, nullptr, 0}}
#define NERROR(name) Error name = {NOTSET, {0, nullptr, 0}}

#define UNSET                                                                  \
	err->code = NOTSET;                                                        \
	if (err->message.ptr != nullptr)                                           \
	{                                                                          \
		free(err->message.ptr);                                                \
		err->message.ptr = nullptr;                                            \
		err->message.len = 0, err->message.cap = 0;                            \
	}

#define SET_ERR(_code_arg, _msg_arg)                                           \
	{                                                                          \
		err->code = _code_arg;                                                 \
		auto len  = strlen(_msg_arg);                                          \
		if (len)                                                               \
		{                                                                      \
			if (len > err->message.cap)                                        \
			{                                                                  \
				char* new_ptr;                                                 \
				if ((new_ptr = (char*) realloc(err->message.ptr,               \
											   err->message.cap + len)) ==     \
					nullptr)                                                   \
				{                                                              \
					err->code = ERR_NULL_POINTER;                              \
					if (err->message.ptr != nullptr)                           \
					{                                                          \
						free(err->message.ptr);                                \
					}                                                          \
					err->message.len = 0, err->message.cap = 0;                \
				}                                                              \
				else                                                           \
				{                                                              \
					err->message.ptr = new_ptr;                                \
					err->message.cap += len, err->message.len = len;           \
					strncpy(err->message.ptr, _msg_arg, len);                  \
				}                                                              \
			}                                                                  \
			else                                                               \
			{                                                                  \
				err->message.len = len;                                        \
				strncpy(err->message.ptr, _msg_arg, len);                      \
			}                                                                  \
		}                                                                      \
	}

#define FE_ERROR                                                               \
	if (error.message.ptr != nullptr)                                          \
	{                                                                          \
		free(error.message.ptr);                                               \
	}

#define FE_NERROR(name) free(name.message.ptr)

const char* getErrorMessage(ErrorCode code);