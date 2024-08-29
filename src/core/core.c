#include "./core.h"

Result coreCreate( Core *const coreptr )
{
	WindowBuf windowbuf;
	if ( windowbufCreate( &windowbuf ) != SUCCESSFUL )
	{
		return OUT_OF_MEMORY;
	}
	Info info;
	if ( infoCreate( &info ) != SUCCESSFUL )
	{
		return OUT_OF_MEMORY;
	}
	coreptr->offset = offsetCreate();
	coreptr->lines = NULL;

	return SUCCESSFUL;
}

Result coreInit( Core *const coreptr )
{
	winsizeUpdate();

	enableRawMode();

	windowbufResize( &coreptr->window );
	// FILE *fileptr = fileOpen( cmds->path, "r+" );
	// Lines *const linesptr = linesFileToLines( fileptr );
	return SUCCESSFUL;
}

Result coreLoop( Cmds *const cmdsptr )
{
	Core core;
	if ( coreCreate( &core ) != SUCCESSFUL )
	{
		return FAILED;
	}

	coreInit( &core );

	do
	{
		display( &core );
		keyProcess( &core );
	} while ( core.exit == false );

	coreExit( &core );

	return SUCCESSFUL;
}

void coreExit( Core *const coreptr )
{
	disableRawMode();

	windowbufFree( &coreptr->window );

	infoFree( &coreptr->info );

	linesFree( coreptr->lines );

	write( STDOUT_FILENO, SCREEN_CLEAR, 4 );
	write( STDOUT_FILENO, CURSOR_AT_START, 3 );
}

FILE *fileOpen( char *const path, const char *const mode )
{
	FILE *file = NULL;
	if ( ( file = fopen( path, mode == NULL ? DEFAULT_OPEN_MODE : mode ) ) ==
	     NULL ) // TOOD: validate open mode in cli parser
	{
		return NULL;
	}
	return file;
}

Result enableRawMode()
{
	struct termios rawterm;

	if ( tcgetattr( STDIN_FILENO, &rawterm ) < 0 )
	{
		return FAILED;
	}

	ORGTERMIOS = rawterm;

	rawterm.c_iflag &= ~( BRKINT | ICRNL | INPCK | ISTRIP | IXON );
	rawterm.c_oflag &= ~( OPOST );
	rawterm.c_cflag |= ( CS8 );
	rawterm.c_lflag &= ~( ECHO | ICANON | IEXTEN | ISIG );
	rawterm.c_cc[VMIN] = 0;
	rawterm.c_cc[VTIME] = KEYBINDING_TIMOEOUT;

	if ( tcsetattr( STDIN_FILENO, TCSAFLUSH, &rawterm ) < 0 )
	{
		return FAILED;
	}
	return SUCCESSFUL;
}

Result disableRawMode()
{
	if ( tcsetattr( STDIN_FILENO, TCSAFLUSH, &ORGTERMIOS ) < 0 )
	{
		return FAILED;
	}
	return SUCCESSFUL;
}
