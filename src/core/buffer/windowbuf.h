#pragma once

#include "../../errors.h"

#include <stdio.h>
#include <sys/ioctl.h>
#include <sys/types.h>

struct WindowBuf {
	// The size of the capacity is equal to multiply width and height of the terminal
	unsigned int cap;
	char *ptr;
	unsigned int len;
};

typedef struct WindowBuf WindowBuf;

extern WindowBuf windowbufCreate();

extern Result windowbufResize(WindowBuf *windowbufptr, const u_int16_t row, const u_int16_t col);

extern Result windowbufWrite(const WindowBuf *winbufptr);

extern void windowbufFree(WindowBuf *const winbufptr);

extern Result windowbufAppend(WindowBuf *winbufptr, char *const content, size_t len);
