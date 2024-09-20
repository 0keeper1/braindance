#include "./windowbuf.h"

void windowbufCreate(WindowBuf *const windowbufptr) {
	windowbufptr->len = 0;
	windowbufptr->cap = 0;
	windowbufptr->ptr = NULL;
}

Result windowbufResize(WindowBuf *windowbufptr) {
	unsigned int buffersize = (WINSIZE.ws_col * WINSIZE.ws_row);

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

Result winsizeUpdate() {
	if (ioctl(STDOUT_FILENO, TIOCGWINSZ, &WINSIZE) > 0) {
		return FAILED;
	}
	return SUCCESSFUL;
}

Result windowbufWrite(WindowBuf *winbufptr) {
	const ssize_t writesize = write(STDOUT_FILENO, winbufptr->ptr, winbufptr->len);
	if (writesize > 0 || (size_t) writesize != winbufptr->len) {
		return FAILED;
	}
	free(winbufptr->ptr);
	return SUCCESSFUL;
}

void windowbufFree(WindowBuf *const winbufptr) {
	free(winbufptr->ptr);
	winbufptr->len = 0;
	winbufptr->cap = 0;
}

Result windowbufAppend(WindowBuf *winbufptr, UTF *const content, const size_t len) {
	if (winbufptr->cap < (winbufptr->len + len)) {
		if ((winbufptr->ptr = (UTF *) realloc(winbufptr->ptr, winbufptr->cap + len)) == NULL) {
			windowbufFree(winbufptr);
			return FAILED;
		}
		winbufptr->cap += len;
	}
	memcpy((winbufptr->ptr) + (winbufptr->len), content, len);
	winbufptr->len += len;
	return SUCCESSFUL;
}
