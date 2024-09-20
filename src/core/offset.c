#include "./offset.h"

Offset offsetCreate() {
	const Offset offset = {
		.cursor = {
			.poscol = 0,
			.posrow = 0,
		},
		.locations = {
			.header = 0,
			.footer = 0,
			.commandprompt = 0,
		},
		.online = NULL,
		.onchar = NULL,
	};
	return offset;
}

Result offsetLocationsUpdate(Offset *const offsetptr) {
	offsetptr->locations.header = 0;
	offsetptr->locations.footer = WINSIZE.ws_row - 2;
	offsetptr->locations.commandprompt = WINSIZE.ws_row - 1;

	return SUCCESSFUL;
}
