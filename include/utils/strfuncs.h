#pragma once

#include <stddef.h>
#include <stdio.h>

/**
 * @brief Read a file and write the contents to the allocated buffer and set length and capacity based on what was read and allocated
 * @param file Pointer to file
 * @param len Length indicating the number of characters in the buffer
 * @param cap Capacity of the allocated buffer
 * @return Pointer to the allocated memory holding the file content
 * @throw ERR_NULL_POINTER If `file`, `len`, or `cap` is NULL
 * @throw FILE_ERR_SEEK_FAILED If `fseek` fails while seeking the file
 * @throw STD_ERR_REQUEST_FOR_MEMORY_FAILED If memory allocation fails
 */
char* strFromFile(FILE* restrict file,
				  size_t* restrict len,
				  size_t* restrict cap) __attribute__((nonnull(1, 2, 3)));

/**
 * @brief Sets a new capacity for the string. If the current length exceeds the new capacity, the string may become corrupted
 * @param self A pointer to the string structure
 * @param new_capacity The new capacity to allocate for the string
 * @throw ERR_NULL_POINTER If `self` is NULL
 * @throw STD_ERR_REALLOCATION_FAILED If reallocating the buffer with the new capacity fails
 */
void strSetCapacity(void* restrict self, size_t new_capacity)
	__attribute__((nonnull(1)));

/**
 * @brief Adjusts the capacity to fit the current length of the string
 * @param self Pointer to the anonymous string structure
 * @throw ERR_NULL_POINTER If `self` is NULL
 * @throw STD_ERR_REALLOCATION_FAILED If reallocating the buffer with the current length fails
 */
void strFitCapacity(void* restrict self) __attribute__((nonnull(1)));

/**
 * @brief Create a copy of the string in a newly allocated heap area
 * @param self Pointer to the anonymous string structure
 * @return A copy of the string with its capacity adjusted to its current length
 * @throw ERR_NULL_POINTER If `self` is NULL
 * @throw STD_ERR_REQUEST_FOR_MEMORY_FAILED If memory allocation fails for the new string copy
 * @throw STD_ERR_COPY_STRING_FAILED If copying the string fails
 */
char* strCopy(void* restrict self) __attribute__((nonnull(1)));

/**
 * @brief Sets the capacity to zero and frees the allocated memory
 * @param self Pointer to the anonymous string structure
 * @throw ERR_NULL_POINTER If `self` is NULL
 */
void strDrop(void* restrict self) __attribute__((nonnull(1)));

/**
 * @brief Clears the string by setting all characters in the allocated area to zero
 * @param self Pointer to the anonymous string structure
 * @throw ERR_NULL_POINTER If `self` is NULL
 */
void strClear(void* restrict self) __attribute__((nonnull(1)));