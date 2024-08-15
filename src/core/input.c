#include "./input.h"

const Key *const keyRead()
{
	static Key key;

	{
		key.character = 0;
		key.isbtn = false;
		key.isctrl = false;
		key.isalt = false;
		key.isfn = false;
	}

	unsigned char inputs[6] = { 0 };

	ssize_t rbytes;
	if ( ( rbytes = read( STDIN_FILENO, inputs, 6 ) ) == -1 )
	{
		return NULL;
	}
	printf( "+ %lu +\n", rbytes );
	printf( "%d-%d-%d-%d-%d-%d\r\n", inputs[0], inputs[1], inputs[2], inputs[3], inputs[4], inputs[5] );
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
			key.isbtn = true;
			return &key;
		}
		if ( iscntrl( inputs[0] ) )
		{
			key.character = inputs[0] + 'a' - 1;
			key.isctrl = true;
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
		if ( inputs[0] == 27 && inputs[1] != 0 )
		{
			key.character = inputs[1];
			key.isalt = true;
			return &key;
		}
	}
	else if ( rbytes == 3 )
	{
		if ( inputs[0] == 27 && inputs[1] == 91 )
		{
			switch ( inputs[2] )
			{
			case 'A':
				key.button = ARROW_UP;
				key.isbtn = true;
				return &key;
			case 'B':
				key.button = ARROW_DOWN;
				key.isbtn = true;
				return &key;
			case 'C':
				key.button = ARROW_RIGHT;
				key.isbtn = true;
				return &key;
			case 'D':
				key.button = ARROW_LEFT;
				key.isbtn = true;
				return &key;
			case 72:
				key.button = FN_ARROW_LEFT;
				key.isbtn = true;
				return &key;
			case 70:
				key.button = FN_ARROW_RIGHT;
				key.isbtn = true;
				return &key;
			default:
				break;
			}
		}
	}
	else if ( rbytes == 4 )
	{
	}
	else if ( rbytes == 6 )
	{
		if ( inputs[0] == 27 && inputs[1] == 91 && inputs[2] == 49 && inputs[3] == 59 )
		{
			unsigned char inp4 = inputs[4];
			switch ( inputs[5] )
			{
			case 'A':
				if ( inp4 == 50 )
				{
					key.button = SHIFT_ARROW_UP;
				}
				else if ( inp4 == 51 )
				{
					key.button = ALT_ARROW_UP;
				}
				else if ( inp4 == 52 )
				{
					key.button = SHIFT_ALT_ARROW_UP;
				}
				else if ( inp4 == 53 )
				{
					key.button = CTRL_ARROW_UP;
				}
				else if ( inp4 == 54 )
				{
					key.button = SHIFT_CTRL_ARROW_UP;
				}
				key.isbtn = true;
				return &key;
			case 'B':
				if ( inp4 == 50 )
				{
					key.button = SHIFT_ARROW_DOWN;
				}
				else if ( inp4 == 51 )
				{
					key.button = ALT_ARROW_DOWN;
				}
				else if ( inp4 == 52 )
				{
					key.button = SHIFT_ALT_ARROW_DOWN;
				}
				else if ( inp4 == 53 )
				{
					key.button = CTRL_ARROW_DOWN;
				}
				else if ( inp4 == 54 )
				{
					key.button = SHIFT_CTRL_ARROW_DOWN;
				}
				key.isbtn = true;
				return &key;
			case 'C':
				if ( inp4 == 50 )
				{
					key.button = SHIFT_ARROW_RIGHT;
				}
				else if ( inp4 == 51 )
				{
					key.button = ALT_ARROW_RIGHT;
				}
				else if ( inp4 == 52 )
				{
					key.button = SHIFT_ALT_ARROW_RIGHT;
				}
				else if ( inp4 == 53 )
				{
					key.button = CTRL_ARROW_RIGHT;
				}
				else if ( inp4 == 54 )
				{
					key.button = SHIFT_CTRL_ARROW_RIGHT;
				}
				key.isbtn = true;
				return &key;
			case 'D':
				if ( inp4 == 50 )
				{
					key.button = SHIFT_ARROW_LEFT;
				}
				else if ( inp4 == 51 )
				{
					key.button = ALT_ARROW_LEFT;
				}
				else if ( inp4 == 52 )
				{
					key.button = SHIFT_ALT_ARROW_LEFT;
				}
				else if ( inp4 == 53 )
				{
					key.button = CTRL_ARROW_LEFT;
				}
				else if ( inp4 == 54 )
				{
					key.button = SHIFT_CTRL_ARROW_LEFT;
				}
				key.isbtn = true;
				return &key;
			default:
				break;
			}
		}
	}

	return &key;
}