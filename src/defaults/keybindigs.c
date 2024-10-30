#include "defaults/keybindigs.h"

Result keyactionSWITCH_LAYOUT(Core *const coreptr) {
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
	return SUCCESSFUL;
}

Result keyactionSWITCH_LAYOUT_TO_PROMPT(Core *const coreptr) {
	coreptr->layout = PROMPT;
	return SUCCESSFUL;
}

Result keyactionSWITCH_LAYOUT_TO_EDITOR(Core *const coreptr) {
	coreptr->layout = EDITOR;
	return SUCCESSFUL;
}

Result keyactionEXIT(Core *const coreptr) {
	coreptr->exit = true;
	return SUCCESSFUL;
}
