#include "./window.h"

Window windowCreate( int terminal_width, int terminal_height )
{
	int cap = terminal_width * terminal_height;
	UTF *bufferptr = ( UTF * )calloc( cap, sizeof( UTF ) );
	Window window = { .cap = cap, .len = 0, .ptr = bufferptr };
	return window;
}