#include "./input.h"

const Key *const keyRead()
{
	static Key key;

	{
		key.character = '\0';
		key.is_ctrl = false;
		key.is_alt = false;
		key.is_fn = false;
	}

	unsigned char inputs[6] = { 0 };

	ssize_t rbytes;
	if ( ( rbytes = read( STDIN_FILENO, inputs, 6 ) ) == -1 )
	{
		return NULL;
	}
	printf( "+ %lu +\n", rbytes );
	if ( rbytes == 0 )
	{
		key.character = '\0';
		return &key;
	}

	if ( rbytes == 1 )
	{
		if ( inputs[0] == 13 )
		{
			key.button = ENTER;
			key.is_ctrl = true;
			return &key;
		}
		if ( inputs[0] <= 127 && inputs[0] >= 32 )
		{
			key.character = inputs[0];
			return &key;
		}
	}

	else if ( rbytes == 2 )
	{
	}
	else if ( rbytes == 3 )
	{
	}
	else if ( rbytes == 4 )
	{
	}

	printf( "%d-%d-%d-%d-%d-%d\r\n", inputs[0], inputs[1], inputs[2], inputs[3], inputs[4], inputs[5] );
	return &key;
}
