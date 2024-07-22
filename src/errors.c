#include "errors.h"

#ifndef DEBUG
void printErr( Result err )
{
	char *message = "";
	switch ( err )
	{
	case SUCCESSFUL:
		message = "Successful.";
		break;
	default:
		break;
	}

	printf( "%s", message );
}
#endif