#pragma once

#include "../errors.h"
#include "../settings.h"

#include "limits.h"
#include "stdlib.h"

typedef struct Info {
	char *path;
	char *cwd;
	char *name;
	char *ext;
} Info;

extern Info infoCreate();

extern void infoFree(const Info *const info_ptr);
