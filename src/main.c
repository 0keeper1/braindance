#include "./cmdline/cli.h"
#include "./core/core.h"
#include "./errors.h"
#include "./settings.h"

#include <stdio.h>
#include <stdlib.h>

const char *HELP = "usage: bd [OPTIONS] <FILE PATH>\n\t-h | --help\tShowed this message.\n\r";

int main( int argc, char *argv[] )
{
	Cmds commands = createCmds();
	Result err;
	if ( ( err = parseCli( argc, argv, &commands ) ) != SUCCESSFUL )
	{
		printerr( err );
		return EXIT_FAILURE;
	}

	if ( commands.flags.help == true )
	{
		puts( HELP );
		return EXIT_SUCCESS;
	}
	else if ( commands.path == NULL || checkPath( ( char * )commands.path ) != CLI_IS_FILE )
	{
		fprintf( stderr, "Enter a Specific file path to edit.\n" );
		return EXIT_FAILURE;
	}

	if ( coreLoop( &commands ) == SUCCESSFUL )
	{
		return EXIT_SUCCESS;
	}

	return EXIT_FAILURE;
}
