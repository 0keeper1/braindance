#pragma once

#include "options.h"

// UTF is important because this one handle non english languages.
#define UTF UTF_8

// Default name for new files
#define DEFAULT_SCRATCH_FILE_NAME "SCRATCH"

// Default allocation size for new lines
#define DEFAULT_ALLOCATION_SIZE_PER_LINE 80

#define REALLOCATE_SIZE_TO_INCREASE_CAP 20

#define DEFAULT_OPEN_MODE READ_WRITE_MODE
