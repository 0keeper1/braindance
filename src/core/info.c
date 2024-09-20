#include "./info.h"

Info infoCreate() {
	const Info info = {.path = NULL, .cwd = NULL, .name = NULL, .ext = NULL};
	return info;
}

void infoFree(const Info *const infoptr) {
	free(infoptr->cwd);
	free(infoptr->ext);
	free(infoptr->name);
	free(infoptr->path);
}
