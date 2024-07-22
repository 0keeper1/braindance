#include "./fileh.h"

FILE *fileOpen( char *const path )
{
	FILE *file = NULL;
	if ( ( file = fopen( path, "rb" ) ) == NULL )
	{
		return NULL;
	}
	return file;
}
