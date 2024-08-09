#include "./windowbuf.h"

WindowBuf windowbufCreate()
{
	WindowBuf winbuf = { .cap = ( WINSIZE.ws_col * WINSIZE.ws_row ), .len = 0 };
	winbuf.ptr = ( UTF * )calloc( winbuf.cap, sizeof( UTF ) );
	return winbuf;
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
	auto writesize = write( STDOUT_FILENO, winbufptr->ptr, winbufptr->len );
	if ( writesize > 0 || ( size_t )writesize != winbufptr->len )
	{
		return FAILED;
	}
	memset( winbufptr->ptr, '\0', winbufptr->cap );
	return SUCCESSFUL;
}

inline void windowbufFree( WindowBuf *const winbufptr )
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
