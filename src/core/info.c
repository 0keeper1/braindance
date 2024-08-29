#include "./info.h"

Result infoCreate( Info *infoptr )
{
	UTF *name, *cwd, *path, *ext;

	if ( ( name = ( UTF * )calloc( 20, sizeof( UTF ) ) ) == NULL ||
	     ( cwd = ( UTF * )calloc( _POSIX_PATH_MAX, sizeof( UTF ) ) ) == NULL ||
	     ( path = ( UTF * )calloc( _POSIX_PATH_MAX, sizeof( UTF ) ) ) == NULL ||
	     ( ext = ( UTF * )calloc( 4, sizeof( UTF ) ) ) == NULL )
	{
		return OUT_OF_MEMORY;
	}

	infoptr->name = name;
	infoptr->cwd = cwd;
	infoptr->path = path;
	infoptr->ext = ext;

	return SUCCESSFUL;
}

void infoFree( Info *const infoptr )
{
	free( infoptr->cwd );
	free( infoptr->ext );
	free( infoptr->name );
	free( infoptr->path );
}