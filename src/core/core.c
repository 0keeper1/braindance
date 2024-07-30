#include "./core.h"

Core coreCreate( Lines *const lines, Window *const window )
{
	Core core = { .exit = false, .lines = lines, .window = window };
	return core;
}

Result coreLoop( Core *const core )
{
	while ( core->exit == false )
	{
		//update
		//print
	}

	return SUCCESSFUL;
}

Result coreRun( Cmds *const cmds )
{
	FILE *file;
	Lines *firstline, *lines;
	Window *window;

	signal( SIGWINCH, termResizeSignal );

	coreLoop( NULL );

	// file = fileOpen( cmds->path, cmds->open_mode );
	// lines = linesFileToLines( file );
	// window = windowCreate();
	// init
	// {
	// 	coreCreate( lines, );
	// }

#ifdef DEBUG
	for ( ; lines != NULL; lines = lines->next )
	{
		printf( "[perv: %p next: %p len: %d cap: %d]: %s", lines->perv, lines->next, lines->len, lines->cap,
			lines->ptr );
	}
	printf( "\n" );
#endif

	return SUCCESSFUL;
}