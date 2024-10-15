#include "./info.h"

Info infoCreate() {
	const Info info = {.path = nullptr, .cwd = nullptr, .name = nullptr, .ext = nullptr};
	return info;
}

void infoFree(const Info *const info_ptr) {
	free(info_ptr->cwd);
	free(info_ptr->ext);
	free(info_ptr->name);
	free(info_ptr->path);
}
