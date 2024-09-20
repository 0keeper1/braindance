#include "./offset.h"

Offset offsetCreate() {
	const Offset offset = {
		.cursor = {
			.poscol = 0,
			.posrow = 0,
		},
		.online = NULL,
		.onchar = NULL,
	};
	return offset;
}
