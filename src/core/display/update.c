#include "./update.h"

Result display(const Core *const coreptr) {
	WindowBuf winbuf = windowbufCreate();

	windowbufResize(&winbuf, coreptr->terminal.row, coreptr->terminal.col);

	windowbufAppend(&winbuf, SCREEN_CLEAR, 4);
	windowbufAppend(&winbuf, CURSOR_AT_START, 3);
	windowbufAppend(&winbuf, HIDE_CURSOR, 6);

	writeHeaderBar(&winbuf, coreptr->terminal.col, coreptr->terminal.row);
	writeFooterBar(&winbuf, coreptr->terminal.col, coreptr->terminal.row, coreptr->layout);
	writeLineNumber(&winbuf, coreptr->terminal.row, coreptr->layout);
	writeCommandBar(&winbuf, coreptr->terminal.col, coreptr->terminal.row, coreptr->layout);
	writePrompt(&winbuf, &coreptr->prompt, coreptr->terminal.col, coreptr->terminal.row);

	restoreCursor(&winbuf, &coreptr->prompt, coreptr->terminal.col, coreptr->terminal.row,
	              coreptr->offset.cursor.poscol, coreptr->offset.cursor.posrow,
	              coreptr->layout);
	windowbufAppend(&winbuf, SHOW_CURSOR, 6);

	windowbufWrite(&winbuf);

	free(winbuf.ptr);

	return SUCCESSFUL;
}

void restoreCursor(WindowBuf *const winbufptr, const Prompt *const promptptr,
                   const u_int16_t col, const u_int16_t row,
                   const u_int16_t cursorcolpos, const u_int16_t cursorrowpos,
                   const enum Layout layout) {
	char movelocation[8] = {'\0'};

	switch (layout) {
		case PROMPT:
			sprintf(movelocation, "\x1b[%d;%dH", row, promptptr->len == 0 ? 3 : promptptr->len + 2);
			windowbufAppend(winbufptr, movelocation, 8);
			break;
		case EDITOR:
			sprintf(movelocation, "\x1b[%d;%dH", cursorrowpos, cursorcolpos);
			windowbufAppend(winbufptr, movelocation, 8);
			break;
		default:
			break;
	}
}
