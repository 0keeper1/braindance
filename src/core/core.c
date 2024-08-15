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

Result coreLoop( Core *const core )
{
	coreInit();

	do
	{
		// if ( display( &core->window, &core->offset, core->lines ) )
		// {
		// 	core->exit = true;
		// }
		const Key *key = keyRead();
		if ( key == NULL || ( key->character == 'q' && key->mod == CTRL ) )
		{
			core->exit = true;
		}

		if ( key->mod == BTN )
		{
			printf( "button: %s\r\n", arr[key->button] );
		}
		else if ( key->mod == CTRL )
		{
			printf( "ctrl: %c\r\n", key->character );
		}
		else if ( key->mod == ALT )
		{
			printf( "alt: %c\r\n", key->character );
		}
		else if ( key->mod == FN )
		{
			printf( "fn: %c\r\n", key->character );
		}
		else
		{
			printf( "char: %c\r\n", key->character );
		}

	} while ( core->exit == false );

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
	rawterm.c_cc[VTIME] = 30;

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
