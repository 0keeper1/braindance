#include "errors.h"

void printerr( Result err )
{
	char *message;
	switch ( err )
	{
	case SUCCESSFUL:
		message = "Successful.";
		break;
	case FAILED:
		message = "Failed.";
		break;
	case CLI_INVALID_FALG:
		message = "Invalid input flag.";
		break;
	case OUT_OF_MEMORY:
		message = "Out of memory.";
		break;
	default:
		message = "Unknown Error.";
		break;
	}

	fprintf( stderr, "%s\n", message );
}
