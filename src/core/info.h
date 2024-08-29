#pragma once

#include "../../settings.h"

struct Info
{
	UTF *path;
	UTF *cwd;
	UTF *name;
	UTF *ext;
};

typedef struct Info Info;