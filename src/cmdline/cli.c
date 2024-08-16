#include "cli.h"

bool isFlag( const char *const arg )
{
	if ( arg[0] == '-' || ( arg[0] == '-' && arg[1] == '-' ) )
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool checkFlag( const char *const argument, const char *const small_flag, const char *const large_flag )
{
	return strncmp( argument, small_flag, strlen( small_flag ) ) == 0 ||
	       strncmp( argument, large_flag, strlen( large_flag ) ) == 0;
}

Cmds createCmds()
{
	Cmds commands = { .cwd = NULL, .path = NULL, .help = false, .open_mode = NULL };
	return commands;
}

Result parseCli( int argc, char *const argv[], Cmds *const commands )
{
	commands->cwd = NULL;

	for ( int c = 1; c != argc; c++ )
	{
		if ( isFlag( argv[c] ) )
		{
			if ( checkFlag( argv[c], "-h", "--help" ) )
			{
				commands->help = true;
			}
			else if ( checkFlag( argv[c], "-m", "--mode" ) )
			{
				if ( c + 1 <= argc )
				{
					commands->open_mode = argv[++c];
				}
			}
		}
		else if ( c == ( argc - 1 ) )
		{
			commands->path = argv[c];
		}
	}

	return SUCCESSFUL;
}
