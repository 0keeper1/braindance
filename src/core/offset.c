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

Result offsetLocationsUpdate(Offset *const offsetptr, const u_int16_t row, const u_int16_t col) {
	offsetptr->locations.header = 0;
	offsetptr->locations.footer = row - 2;
	offsetptr->locations.commandprompt = col - 1;

	return SUCCESSFUL;
}
