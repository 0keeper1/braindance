#include "./windowbuf.h"

Result windowbufCreate( WindowBuf *const windowbufptr )
{
	unsigned int buffersize = ( WINSIZE.ws_col * WINSIZE.ws_row );
	windowbufptr->len = 0;
	windowbufptr->cap = buffersize;
	if ( ( windowbufptr->ptr = ( UTF * )calloc( buffersize, sizeof( UTF ) ) ) == NULL )
	{
		return OUT_OF_MEMORY;
	}
	return SUCCESSFUL;
}

Result windowbufResize( WindowBuf *const windowbufptr )
{
	unsigned int buffersize = ( WINSIZE.ws_col * WINSIZE.ws_row );
	if ( ( windowbufptr->ptr = ( UTF * )realloc( windowbufptr->ptr, buffersize ) ) == NULL )
	{
		return OUT_OF_MEMORY;
	}
	windowbufptr->cap = buffersize;
	if ( windowbufptr->len > buffersize )
	{
		windowbufptr->len = buffersize;
	}
	return SUCCESSFUL;
}

Result winsizeUpdate()
{
	if ( ioctl( STDOUT_FILENO, TIOCGWINSZ, &WINSIZE ) > 0 )
	{
		return FAILED;
	}
	return SUCCESSFUL;
}

Result windowbufWrite( WindowBuf *winbufptr )
{
	ssize_t writesize = write( STDOUT_FILENO, winbufptr->ptr, winbufptr->len );
	if ( writesize > 0 || ( size_t )writesize != winbufptr->len )
	{
		return FAILED;
	}
	memset( winbufptr->ptr, '\0', winbufptr->cap );
	return SUCCESSFUL;
}

void windowbufFree( WindowBuf *const winbufptr )
{
	free( winbufptr->ptr );
	winbufptr->len = 0;
	winbufptr->cap = 0;
}

Result windowbufAppend( WindowBuf *const winbufptr, const UTF *content, size_t len )
{
	if ( winbufptr->cap < ( winbufptr->len + len ) )
	{
		if ( ( winbufptr->ptr = ( UTF * )realloc( winbufptr->ptr, winbufptr->cap + len ) ) == NULL )
		{
			windowbufFree( winbufptr );
			return FAILED;
		}
		winbufptr->cap += len;
	}
	memcpy( ( winbufptr->ptr ) + ( winbufptr->len ), content, len );
	winbufptr->len += len;
	return SUCCESSFUL;
}
