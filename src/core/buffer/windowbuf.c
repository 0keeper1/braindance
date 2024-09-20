#include "./windowbuf.h"

#include <termios.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

#include "core.h"


WindowBuf windowbufCreate() {
	const WindowBuf winbuf = {.cap = 0, .ptr = NULL, .len = 0};
	return winbuf;
}

Result windowbufResize(WindowBuf *windowbufptr, const u_int16_t row, const u_int16_t col) {
	const unsigned int buffersize = (col * row);

	windowbufptr->ptr = realloc(windowbufptr->ptr, buffersize);

	if (windowbufptr->ptr == NULL) {
		return OUT_OF_MEMORY;
	}

	windowbufptr->cap = buffersize;
	if (windowbufptr->len > buffersize) {
		windowbufptr->len = buffersize;
	}
	return SUCCESSFUL;
}

Result windowbufWrite(const WindowBuf *winbufptr) {
	const ssize_t writesize = write(STDOUT_FILENO, winbufptr->ptr, winbufptr->len);
	if (writesize > 0 || (size_t) writesize != winbufptr->len) {
		return FAILED;
	}
	return SUCCESSFUL;
}

void windowbufFree(WindowBuf *const winbufptr) {
	free(winbufptr->ptr);
	winbufptr->len = 0;
	winbufptr->cap = 0;
}

Result windowbufAppend(WindowBuf *winbufptr, char *const content, const size_t len) {
	if (winbufptr->cap < (winbufptr->len + len)) {
		if ((winbufptr->ptr = (char *) realloc(winbufptr->ptr, winbufptr->cap + len)) == NULL) {
			windowbufFree(winbufptr);
			return FAILED;
		}
		winbufptr->cap += len;
	}
	memcpy((winbufptr->ptr) + (winbufptr->len), content, len);
	winbufptr->len += len;
	return SUCCESSFUL;
}
