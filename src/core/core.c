#include "./core.h"

Result coreInit()
{
	winsizeUpdate();
	enableRawMode();
	return SUCCESSFUL;
}

Result coreRun( const Cmds *const cmds )
{
	WindowBuf const winbuf = windowbufCreate();
	Offset const offset = offsetCreate();
	FILE *fileptr = fileOpen( cmds->path, cmds->open_mode );
	Lines *const linesptr = linesFileToLines( fileptr );
	Core core = { .exit = false, .lines = linesptr, .window = winbuf, .offset = offset };

	return coreLoop( &core );
}

Result coreLoop( Core *const coreptr )
{
	coreInit();

	do
	{
		// display( coreptr );
		keyProcess( coreptr );
	} while ( coreptr->exit == false );

	coreExit();

	return SUCCESSFUL;
}

void coreExit()
{
	disableRawMode();
	write( STDOUT_FILENO, SCREEN_CLEAR, 4 );
	write( STDOUT_FILENO, CURSOR_AT_START, 3 );
}

FILE *fileOpen( char *const path, const char *const mode )
{
	FILE *file = NULL;
	if ( ( file = fopen( path, mode == NULL ? DEFAULT_OPEN_MODE : mode ) ) == NULL )
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
