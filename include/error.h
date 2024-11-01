#pragma once

#include "buffers/str.h"
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
	Str msg;
} Error;

#define ERR Error* err

#define ERROR Error error = {NOTSET, {0, nullptr, 0}}
#define NERROR(name) Error name = {NOTSET, {0, nullptr, 0}}

#define UNSET                                                                  \
	err->code = NOTSET;                                                        \
	if (err->msg.ptr != nullptr)                                               \
	{                                                                          \
		free(err->msg.ptr);                                                    \
		err->msg.len = 0, err->msg.cap = 0;                                    \
	}

#define SET_ERROR(_code_arg, _msg_arg)                                         \
	{                                                                          \
		err->code = _code_arg;                                                 \
		auto len  = strlen(_msg_arg);                                          \
		if (len)                                                               \
		{                                                                      \
			if (len > err->msg.cap)                                            \
			{                                                                  \
				char* new_ptr;                                                 \
				if ((new_ptr = realloc(err->msg.ptr, err->msg.cap + len)) ==   \
					nullptr)                                                   \
				{                                                              \
					err->code = ERR_NULL_POINTER;                              \
					if (err->msg.ptr != nullptr)                               \
					{                                                          \
						free(err->msg.ptr);                                    \
					}                                                          \
					err->msg.len = 0, err->msg.cap = 0;                        \
				}                                                              \
				else                                                           \
				{                                                              \
					err->msg.ptr = new_ptr;                                    \
					err->msg.cap += len, err->msg.len = len;                   \
					strncpy(err->msg.ptr, _msg_arg, len);                      \
				}                                                              \
			}                                                                  \
			else                                                               \
			{                                                                  \
				err->msg.len = len;                                            \
				strncpy(err->msg.ptr, _msg_arg, len);                          \
			}                                                                  \
		}                                                                      \
	}

#define FE_ERROR free(error.msg.ptr)
#define FE_NERROR(name) free(name.msg.ptr)

const char* getErrorMessage(ErrorCode code);
