#include "./layouts.h"

#include <stdio.h>

void writeHeaderBar(WindowBuf *winbufptr, const u_int16_t col, const u_int16_t row) {
    char *bufptr = malloc(col * sizeof(char));

    windowbufAppend(winbufptr, "\x1b[0;47m", 8);
    for (int i = 0; i < col; i++) {
        bufptr[i] = '#';
    }
    windowbufAppend(winbufptr, bufptr, col);
    windowbufAppend(winbufptr, "\x1b[0m", 4);

    char movelocation[8] = {'\0'};

    sprintf(movelocation, "\x1b[%d;%dH", 0, col / 4);

    windowbufAppend(winbufptr, movelocation, 8);
    windowbufAppend(winbufptr, "\x1b[1;30;47mBRAINDANCE\x1b[0;0;0m", 21);

    free(bufptr);
}

void writeSideBars(WindowBuf *const winbufptr) {
}

void writeFooterBar(WindowBuf *const winbufptr, const u_int16_t col, const u_int16_t row) {
    char movelocation[8] = {'\0'};
    sprintf(movelocation, "\x1b[%d;%dH", row - 1, 0);

    windowbufAppend(winbufptr, movelocation, 8);

    char *bufptr = malloc(col * sizeof(char));

    windowbufAppend(winbufptr, "\x1b[0;47m", 8);
    for (int i = 0; i < col; i++) {
        bufptr[i] = '#';
    }
    windowbufAppend(winbufptr, bufptr, col);
    windowbufAppend(winbufptr, "\x1b[0m", 4);

    free(bufptr);
}

void writeCommandBar(WindowBuf *const winbufptr, const u_int16_t col, const u_int16_t row) {
    // show commands
    char movelocation[8] = {'\0'};
    sprintf(movelocation, "\x1b[%d;%dH", row, 0);

    windowbufAppend(winbufptr, movelocation, 8);
    windowbufAppend(winbufptr, "> ", 2);
}

void writeContent(WindowBuf *const winbufptr) {
}

void writeLineNumber(WindowBuf *const winbufptr, const u_int16_t row) {
    char movelocation[8] = {'\0'};
    sprintf(movelocation, "\x1b[%d;%dH", 2, 0);

    windowbufAppend(winbufptr, movelocation, 8);

    for (int i = 0; i < row - 3; i++) {
        windowbufAppend(winbufptr, "~\n\r", 3);
    }
}
