#include "./offset.h"

Offset offsetCreate() {
	const Offset offset = {
		.cursor = {
			.poscol = 0,
			.posrow = 0,
		},
		.promptcursor = {
			.poscol = 0,
			.posrow = 0,
		},
		.online = nullptr,
		.onchar = nullptr,
	};
	return offset;
}
