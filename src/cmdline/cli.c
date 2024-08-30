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
	Cmds commands = { .cwd = NULL, .path = NULL, .flags.help = false };
	return commands;
}

Result parseCli( int argc, char *const argv[], Cmds *const commands )
{
	for ( int c = 1; c != argc; c++ )
	{
		if ( isFlag( argv[c] ) )
		{
			if ( checkFlag( argv[c], "-h", "--help" ) )
			{
				commands->flags.help = true;
				return SUCCESSFUL;
			}
			else
			{
				return CLI_INVALID_FALG;
			}
		}
		else if ( c == ( argc - 1 ) )
		{
			commands->path = realpath( argv[c], NULL );
		}
	}
	commands->cwd = getcwd( NULL, 0 );
	return SUCCESSFUL;
}

Result checkPath( const char *const pathptr )
{
	struct stat path_stat;
	stat( pathptr, &path_stat );
	if ( S_ISDIR( path_stat.st_mode ) )
	{
		return CLI_IS_DIR;
	}
	else if ( S_ISREG( path_stat.st_mode ) )
	{
		return CLI_IS_FILE;
	}
	else
	{
		return CLI_INVALID_PATH;
	}
}