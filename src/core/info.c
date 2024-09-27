#include "./info.h"

Info infoCreate() {
	const Info info = {.path = nullptr, .cwd = nullptr, .name = nullptr, .ext = nullptr};
	return info;
}

void infoFree(const Info *const infoptr) {
	free(infoptr->cwd);
	free(infoptr->ext);
	free(infoptr->name);
	free(infoptr->path);
}
