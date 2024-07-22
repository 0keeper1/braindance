#include "path.h"

bool isPath( const char *path )
{
	if ( !path || !*path || *path != '/' )
	{
		return false;
	}
	for ( ; *path != '\0'; ++path )
	{
		if ( *path == '\'' || *path == '\"' )
		{
			return false;
		}
	}
	return true;
}

enum PathError checkPath( const char *const cwd, const char *const path )
{
	if ( path == NULL )
	{
		return P_PATH_IS_NULL;
	}
	else if ( cwd == NULL )
	{
		return P_CWD_IS_NULL;
	}

	int res = access( path, F_OK );

	if ( res == EACCES )
	{
		return P_PERM_DENIED;
	}
	else if ( res == ENOENT )
	{
		return P_DOES_NOT_EXISTS;
	}
	else if ( res == EROFS )
	{
		return P_INVALID;
	}

	char string_path[strlen( cwd ) + strlen( path )];
	// check string
	strncpy( string_path, cwd, strlen( cwd ) );
	strncat( string_path, "/", 1 );
	strncat( string_path, path, strlen( path ) );

	if ( access( string_path, F_OK ) < 0 )
	{
		return P_IO;
	}

	return P_IS_VALID;
}

int checkAccess( const char *const path )
{
	switch ( access( path, F_OK ) )
	{
	case EACCES:
		return P_PERM_DENIED;
		break;
	case ENOENT:
		return P_DOES_NOT_EXISTS;
		break;
	case EROFS:
		return P_INVALID;
		break;
	default:
		return P_IS_VALID;
		break;
	}
}