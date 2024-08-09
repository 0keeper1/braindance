#include "./core.h"

Result coreInit()
{
	winsizeUpdate();
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
		//print
		//mod
		//update
	} while ( core->exit == false );

	coreExit();

	return SUCCESSFUL;
}

void coreExit() {}

FILE *fileOpen( char *const path, const char *const mode )
{
	FILE *file = NULL;
	if ( ( file = fopen( path, mode == NULL ? DEFAULT_OPEN_MODE : mode ) ) == NULL )
	{
		return NULL;
	}
	return file;
}
