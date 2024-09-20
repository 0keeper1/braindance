#pragma once

#include "../errors.h"
#include "../settings.h"

#include "limits.h"
#include "stdlib.h"

struct Info {
	UTF *path;
	UTF *cwd;
	UTF *name;
	UTF *ext;
};

typedef struct Info Info;

extern Result infoCreate(Info *const infoptr);

extern void infoFree(Info *const infoptr);
