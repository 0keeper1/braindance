#include "./input.h"

const Key *const keyRead()
{
	static Key key;

	{
		key.character = 0;
		key.mod = NOMOD;
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
		key.button = TIMEOUT;
		key.mod |= BTN;
		return &key;
	}

	if ( rbytes == 1 )
	{
		if ( inputs[0] == 13 )
		{
			key.button = ENTER;
			key.mod |= BTN;
			return &key;
		}
		if ( inputs[0] == 127 )
		{
			key.button = BACKSPACE;
			key.mod |= BTN;
			return &key;
		}
		if ( inputs[0] == 27 )
		{
			key.button = ESC;
			key.mod |= BTN;
			return &key;
		}
		if ( iscntrl( inputs[0] ) )
		{
			key.character = inputs[0] + 'a' - 1;
			key.mod |= CTRL;
			return &key;
		}
		if ( inputs[0] <= 126 && inputs[0] >= 32 )
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
			key.mod |= ALT;
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
				key.mod |= BTN;
				return &key;
			case 'B':
				key.button = ARROW_DOWN;
				key.mod |= BTN;
				return &key;
			case 'C':
				key.button = ARROW_RIGHT;
				key.mod |= BTN;
				return &key;
			case 'D':
				key.button = ARROW_LEFT;
				key.mod |= BTN;
				return &key;
			case 72:
				key.button = FN_ARROW_LEFT;
				key.mod |= BTN;
				return &key;
			case 70:
				key.button = FN_ARROW_RIGHT;
				key.mod |= BTN;
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
				key.mod |= BTN;
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
				key.mod |= BTN;
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
				key.mod |= BTN;
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
				key.mod |= BTN;
				return &key;
			default:
				break;
			}
		}
	}

	return &key;
}