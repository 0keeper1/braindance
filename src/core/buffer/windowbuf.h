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
	// The size of the capacity is equal to multiply width and height of the terminal
	unsigned int cap;
	UTF *ptr;
	unsigned int len;
};

typedef struct WindowBuf WindowBuf;

static struct winsize WINSIZE = { 0 };

extern Result winsizeUpdate();

extern Result windowbufCreate( WindowBuf *const windowbufptr );

extern Result windowbufResize( WindowBuf *const windowbufptr );

extern Result windowbufWrite( WindowBuf *winbufptr );

extern void windowbufFree( WindowBuf *const winbufptr );

extern Result windowbufAppend( WindowBuf *const winbufptr, const UTF *content, size_t len );
