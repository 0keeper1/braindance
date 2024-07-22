#include "./core.h"

Core coreCreate() {}

Result loop( Core *const core ) { return SUCCESSFUL; }

Result coreRun( Cmds *const cmds )
{
	FILE *file;
	Lines *lines;

	file = fopen( cmds->path, "r" );
	lines = linesFileToLines( file );

	for ( ; lines->next != NULL; lines = lines->next )
	{
		printf( "[perv: %p next: %p len: %d cap: %d]: %s", lines->perv, lines->next, lines->len, lines->cap,
			lines->ptr );
	}

	return SUCCESSFUL;
}