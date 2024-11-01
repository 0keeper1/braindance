#include "error.h"

const char* getErrorMessage(const enum ErrorCode code)
{
	switch (code)
	{
		case NOTSET:
			return "No Error Reported";
		case FAILED:
			return "FAILED";
		case ERR_NULL_POINTER:
			return "Null pointer";
		case CLI_ERR_INVALID_PATH:
			return "Command Line Invalid Path";
		case CLI_ERR_INVALID_COMMAND:
			return "Command Line Invalid Command";
		case CLI_ERR_MISSING_ARGUMENT:
			return "Command Line Invalid Argument";
		case CLI_ERR_TOO_MANY_ARGUMENTS:
			return "Command Line Too Many Argument";
		case CLI_ERR_COMMAND_NOT_FOUND:
			return "Command Line Not Found";
		case FILE_ERR_FILE_NOT_FOUND:
			return "File Not Found";
		default:
			return "Unknown Error";
	}
}
