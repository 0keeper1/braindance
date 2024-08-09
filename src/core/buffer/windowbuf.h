#pragma once

#include "../../errors.h"
#include "../../settings.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ioctl.h>
#include <termios.h>
#include <unistd.h>

struct WindowBuf
{
	unsigned int cap; // mul width and height
	UTF *ptr;
	size_t len;
};

typedef struct WindowBuf WindowBuf;

static struct winsize WINSIZE = { 0 };

extern Result winsizeUpdate();
extern WindowBuf windowbufCreate();
extern Result windowbufWrite( WindowBuf *winbufptr );
extern inline void windowbufFree( WindowBuf *const winbufptr );
extern Result windowbufAppend( WindowBuf *const winbufptr, const UTF *content, size_t len );
