#pragma once

#include "../errors.h"
#include "../settings.h"

#include "limits.h"
#include "stdlib.h"

struct Info {
	char *path;
	char *cwd;
	char *name;
	char *ext;
};

typedef struct Info Info;

extern Info infoCreate();

extern void infoFree(Info *const infoptr);
