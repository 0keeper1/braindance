#pragma once

#include "../core/buffer/windowbuf.h"
#include "../core/offset.h"
#include "../errors.h"
#include "./layouts.h"

Result display( WindowBuf *const winbufptr, Offset *const offsetptr );