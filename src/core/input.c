#include "./input.h"

#include <buffer/prompt.h>

const Key *keyRead() {
	static Key key; {
		key.character = 0;
		key.mod = NOMOD;
	}

	unsigned char inputs[6] = {0};

	ssize_t rbytes;
	if ((rbytes = read(STDIN_FILENO, inputs, 6)) == -1) {
		return NULL;
	}

	if (rbytes == 0) {
		key.button = NONE;
		key.mod |= (BTN | TIMEOUT);
		return &key;
	}

	if (rbytes == 1) {
		if (inputs[0] == 13) {
			key.button = ENTER;
			key.mod |= BTN;
			return &key;
		}
		if (inputs[0] == 127) {
			key.button = BACKSPACE;
			key.mod |= BTN;
			return &key;
		}
		if (inputs[0] == 27) {
			key.button = ESC;
			key.mod |= BTN;
			return &key;
		}
		if (iscntrl(inputs[0])) {
			key.character = inputs[0] + 'a' - 1;
			key.mod |= CTRL;
			return &key;
		}
		if (inputs[0] <= 126 && inputs[0] >= 32) {
			key.character = inputs[0];
			key.mod |= CHAR;
			return &key;
		}
	} else if (rbytes == 2) {
		if (inputs[0] == 27 && inputs[1] != 0) {
			key.character = inputs[1];
			key.mod |= ALT;
			return &key;
		}
	} else if (rbytes == 3) {
		if (inputs[0] == 27 && inputs[1] == 91) {
			switch (inputs[2]) {
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
	} else if (rbytes == 4) {
		if (inputs[0] == 27 && inputs[1] == 91 && inputs[3] == 126) {
			switch (inputs[2]) {
				case 53:
					key.button = FN_ARROW_UP;
					key.mod |= BTN;
					return &key;
				case 54:
					key.button = FN_ARROW_DOWN;
					key.mod |= BTN;
					return &key;
					break;
				default:
					break;
			}
		}
	} else if (rbytes == 6) {
		if (inputs[0] == 27 && inputs[1] == 91 && inputs[2] == 49 && inputs[3] == 59) {
			const unsigned char inp4 = inputs[4];
			switch (inputs[5]) {
				case 'A':
					if (inp4 == 50) {
						key.button = SHIFT_ARROW_UP;
					} else if (inp4 == 51) {
						key.button = ALT_ARROW_UP;
					} else if (inp4 == 52) {
						key.button = SHIFT_ALT_ARROW_UP;
					} else if (inp4 == 53) {
						key.button = CTRL_ARROW_UP;
					} else if (inp4 == 54) {
						key.button = SHIFT_CTRL_ARROW_UP;
					}
					key.mod |= BTN;
					return &key;
				case 'B':
					if (inp4 == 50) {
						key.button = SHIFT_ARROW_DOWN;
					} else if (inp4 == 51) {
						key.button = ALT_ARROW_DOWN;
					} else if (inp4 == 52) {
						key.button = SHIFT_ALT_ARROW_DOWN;
					} else if (inp4 == 53) {
						key.button = CTRL_ARROW_DOWN;
					} else if (inp4 == 54) {
						key.button = SHIFT_CTRL_ARROW_DOWN;
					}
					key.mod |= BTN;
					return &key;
				case 'C':
					if (inp4 == 50) {
						key.button = SHIFT_ARROW_RIGHT;
					} else if (inp4 == 51) {
						key.button = ALT_ARROW_RIGHT;
					} else if (inp4 == 52) {
						key.button = SHIFT_ALT_ARROW_RIGHT;
					} else if (inp4 == 53) {
						key.button = CTRL_ARROW_RIGHT;
					} else if (inp4 == 54) {
						key.button = SHIFT_CTRL_ARROW_RIGHT;
					}
					key.mod |= BTN;
					return &key;
				case 'D':
					if (inp4 == 50) {
						key.button = SHIFT_ARROW_LEFT;
					} else if (inp4 == 51) {
						key.button = ALT_ARROW_LEFT;
					} else if (inp4 == 52) {
						key.button = SHIFT_ALT_ARROW_LEFT;
					} else if (inp4 == 53) {
						key.button = CTRL_ARROW_LEFT;
					} else if (inp4 == 54) {
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

void keyQueueZero() { memset(&KeyQueue, 0, sizeof(_KeyQueue)); }

Result keyQueueHandler() {
	const Key *key = keyRead();
	if ((KeyQueue.key.mod == (BTN | TIMEOUT) || KeyQueue.key.mod == NOMOD) &&
	    (KeyQueue.key.button == NONE || KeyQueue.key.button == 0)) {
		if (key->mod == NOMOD) {
			return SUCCESSFUL;
		}

		KeyQueue.key = *key;
		KeyQueue.keycounter = 1;
		if (key->mod == CHAR) {
			KeyQueue.commit = true;
			return SUCCESSFUL;
		} else if ((key->mod & CTRL) || (key->mod & ALT) || (key->mod & FN)) {
			KeyQueue.commit = false;
			return SUCCESSFUL;
		} else if ((key->mod & BTN)) {
			KeyQueue.commit = true;
			return SUCCESSFUL;
		}
	} else {
		if (key->mod == (BTN | TIMEOUT) && key->button == NONE) {
			KeyQueue.commit = true;
			return SUCCESSFUL;
		}
		if (((key->mod & CTRL) || (key->mod & ALT) || (key->mod & FN)) &&
		    key->character == KeyQueue.key.character) {
			if (KeyQueue.keycounter + 1 == MAX_KEY_COMBINATION) {
				KeyQueue.commit = true;
				KeyQueue.keycounter++;
				return SUCCESSFUL;
			} else if (KeyQueue.keycounter + 1 < MAX_KEY_COMBINATION) {
				KeyQueue.commit = false;
				KeyQueue.keycounter++;
				return SUCCESSFUL;
			}
		} else {
			KeyQueue.key = *key;
			KeyQueue.keycounter = 1;
			if ((key->mod & CTRL) || (key->mod & ALT) || (key->mod & FN)) {
				KeyQueue.commit = false;
				return SUCCESSFUL;
			}
			KeyQueue.commit = true;
			return SUCCESSFUL;
		}
	}

	return SUCCESSFUL;
}

Result keyExec(Core *const coreptr) {
#include "../keybindings.h"

	if (checkIsInputKey()) {
		switch (coreptr->layout) {
			case PROMPT:
				promptAppend(&coreptr->prompt, KeyQueue.key.character);
				break;
			case EDITOR:
				break;
			default:
				break;
		}
	} else if (checkKeyWithBinding(&EXIT)) {
		coreptr->exit = true;
	} else if (checkKeyWithBinding(&SWITCH_LAYOUT)) {
		switch (coreptr->layout) {
			case PROMPT:
				coreptr->layout = EDITOR;
				break;
			case EDITOR:
				coreptr->layout = PROMPT;
				break;
			default:
				break;
		}
	} else if (checkKeyWithBinding(&SWITCH_LAYOUT_TO_EDITOR)) {
		coreptr->layout = EDITOR;
	} else if (checkKeyWithBinding(&SWITCH_LAYOUT_TO_PROMPT)) {
		coreptr->layout = PROMPT;
	}

	return SUCCESSFUL;
}

bool checkIsInputKey() {
	if (KeyQueue.key.mod == CHAR && KeyQueue.keycounter == 1 && KeyQueue.commit == true) {
		return true;
	}
	return false;
}

bool checkKeyWithBinding(const struct Keybind *const keybindptr) {
	if (keybindptr->character == KeyQueue.key.character && keybindptr->modifier == KeyQueue.key.mod &&
	    keybindptr->repeat == KeyQueue.keycounter && KeyQueue.commit == true) {
		return true;
	}
	return false;
}

Result keyProcess(Core *const coreptr) {
	if (keyQueueHandler() == FAILED) {
		return FAILED;
	}

	if (keyExec(coreptr) == FAILED) {
		return FAILED;
	}

	if (KeyQueue.commit == true) {
		keyQueueZero();
	}
	return SUCCESSFUL;
}
