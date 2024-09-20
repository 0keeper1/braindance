#include "./layouts.h"

void writeHeaderBar(WindowBuf *winbufptr) {
	windowbufAppend(winbufptr, CURSOR_AT_START, 3);
	auto wins = WINSIZE.ws_row;
	auto wind = WINSIZE.ws_col;
	printf("%d - %d \r\n", wins, wind);
	for (uint i = 0; i < WINSIZE.ws_row; i++) {
		windowbufAppend(winbufptr, &HEADER_SYMBOL, 1);
	}
}

void writeSideBars(Core *const coreptr) {
}

void writeFooterBar(Core *const coreptr) {
}

void writeCommandBar(Core *const coreptr) {
}

void writeContent(Core *const coreptr) {
}

void writeLineNumber(Core *const coreptr) {
}
