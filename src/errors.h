#pragma once

typedef enum Result {
	SUCCESSFUL,
	FAILED,
	CLI_INVALID_FLAG,
	CLI_IS_DIR,
	CLI_IS_FILE,
	CLI_INVALID_PATH,
	OUT_OF_MEMORY,
} Result;

void printerr(Result err);
