#include "./termutils.h"

void termResizeSignal( int sig )
{
	if ( sig == SIGWINCH )
	{
		struct winsize winsz;

		ioctl( 0, TIOCGWINSZ, &winsz );
		printf( "SIGWINCH raised, window size: %d rows / %d columns\n", winsz.ws_row, winsz.ws_col );
	}
}