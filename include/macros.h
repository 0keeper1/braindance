#pragma once

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
 * @brief A simple error catcher to reduce repetitive checks like "if (Error.code != NOTSET) {}"
 * @param ... Run this block in condition
 */
#define CATCH(...)                                                             \
	if (ERROR.code != NOTSET)                                                  \
		__VA_ARGS__;

/**
 * @brief Catch a specific error code
 * @param error_code The error code you want to catch
 */
#define CATCH_ERROR(error_code, ...)                                           \
	if (ERROR.code == error_code)                                              \
		__VA_ARGS__;
