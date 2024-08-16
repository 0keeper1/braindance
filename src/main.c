#include "./cmdline/cli.h"
#include "./core/core.h"
#include "./settings.h"
#include "./utils/path.h"
#include <stdio.h>
#include <stdlib.h>

const char *HELP = "usage: bd [OPTIONS] <FILE PATH>\n\t-h | --help\tShowed this message.\n\t-m <MODE> | --mode "
		   "<MODE>\tOpen file mode (default: r+)";

int main( int argc, char *argv[] )
{
	Cmds commands = createCmds();

	if ( parseCli( argc, argv, &commands ) != 0 )
	{
		return EXIT_FAILURE;
	}
	if ( commands.help == true )
	{
		puts( HELP );
		return EXIT_SUCCESS;
	}
	else if ( commands.path == NULL )
	{
		commands.path = DEFAULT_SCRATCH_FILE_NAME;
	}
	// else if ( checkPath( commands.cwd, commands.path ) == P_IS_VALID )
	// {
	// 	printf( "\nCWD: %s | FILE: %s\n", commands.cwd, commands.path );
	// }

	if ( coreRun( &commands ) == SUCCESSFUL )
	{
		return EXIT_SUCCESS;
	}
	else
	{
		return EXIT_FAILURE;
	}
}
