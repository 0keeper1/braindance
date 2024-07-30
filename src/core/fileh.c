#include "./fileh.h"

FILE *fileOpen( char *const path, const char *const mode )
{
	FILE *file = NULL;
	if ( ( file = fopen( path, mode == NULL ? DEFAULT_OPEN_MODE : mode ) ) == NULL )
	{
		return NULL;
	}
	return file;
}
