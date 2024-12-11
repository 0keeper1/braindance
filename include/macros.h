#pragma once

#include "stdlib.h"
#include "string.h"
#include <stddef.h>

/**
 * @brief Generate an anonymous String struct
 * @param name Name of string field
 */
#define STRING(name)                                                           \
	struct                                                                     \
	{                                                                          \
		size_t cap;                                                            \
		char* ptr;                                                             \
		size_t len;                                                            \
	} name

/**
 * @brief Casts a `void*` pointer to a specific type and creates a variable with a combined name.
 * @param type The type to which the `void*` pointer should be cast.
 * @param variable The `void*` variable to be cast to the specified type.
 */
#define CAST(type, variable) type* type##_##variable = (type*) variable;

/**
 *	@brief Set Char struct perv pointer
 *	@param self Char object pointer
 *	@param prev Previous Char pointer
 */
#define SET_CHAR_PERV(self, prev) self->prev = prev

/**
 *	@brief Set Char struct next pointer
 *	@param self Char object pointer
 *	@param next Next Char pointer
 */
#define SET_CHAR_NEXT(self, next) self->next = next

/**
 * @brief A simple error catcher to reduce repetitive checks like "if (Error.code != NOTSET) {}"
 * @param ... Run this block in condition
 */
#define CATCH(...)                                                             \
	if (Error.code != NOTSET)                                                  \
		__VA_ARGS__;

/**
 * @brief Catch a specific error code
 * @param error_code The error code you want to catch
 */
#define CATCH_ERROR(error_code, ...)                                           \
	if (Error.code == error_code)                                              \
		__VA_ARGS__;

/**
 * @brief Reset Error code to NOTSET
 */
#define RESET_ERROR Error.code = NOTSET

/**
 * @brief Set ERROR code
 * @param error_code ERROR code ErrorCode
 */
#define SET_ERROR_CODE(error_code) Error.code = error_code

/**
 * @brief Set ERROR message
 * @param msg Message that will set to Global ERROR
 */
#define SET_ERROR_MESSAGE(msg)                                                 \
	{                                                                          \
		const size_t len = strlen(msg);                                        \
		if (len)                                                               \
		{                                                                      \
			if (len > Error.message.cap)                                       \
			{                                                                  \
				char* new_ptr;                                                 \
				if ((new_ptr = (char*) realloc(Error.message.ptr,              \
											   Error.message.cap + len)) ==    \
					nullptr)                                                   \
				{                                                              \
					Error.code = ERR_NULL_POINTER;                             \
					if (Error.message.ptr != nullptr)                          \
					{                                                          \
						free(Error.message.ptr);                               \
					}                                                          \
					Error.message.len = 0, Error.message.cap = 0;              \
					Error.code = STD_ERR_REALLOCATION_FAILED;                  \
				}                                                              \
				else                                                           \
				{                                                              \
					Error.message.ptr = new_ptr;                               \
					Error.message.cap += len, Error.message.len = len;         \
					if (strncpy(Error.message.ptr, msg, len) == nullptr)       \
					{                                                          \
						Error.code = STD_ERR_COPY_STRING_FAILED;               \
					}                                                          \
				}                                                              \
			}                                                                  \
			else                                                               \
			{                                                                  \
				Error.message.len = len;                                       \
				if (strncpy(Error.message.ptr, msg, len) == nullptr)           \
				{                                                              \
					Error.code = STD_ERR_COPY_STRING_FAILED;                   \
				}                                                              \
			}                                                                  \
		}                                                                      \
	}
