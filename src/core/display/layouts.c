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

void writeFooterBar(WindowBuf *const winbufptr, const u_int16_t col, const u_int16_t row, const enum Layout layout) {
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

    sprintf(movelocation, "\x1b[%d;%dH", row - 1, col - 4);

    windowbufAppend(winbufptr, movelocation, 8);

    switch (layout) {
        case EDITOR:
            windowbufAppend(winbufptr, "\x1b[7mE\x1b[0m", 9);
            break;
        case PROMPT:
            windowbufAppend(winbufptr, "\x1b[7mP\x1b[0m", 9);
            break;
        default:
            break;
    }

    free(bufptr);
}

void writeCommandBar(WindowBuf *const winbufptr, const u_int16_t col, const u_int16_t row, const enum Layout layout) {
    // show commands
    char movelocation[8] = {'\0'};
    sprintf(movelocation, "\x1b[%d;%dH", row, 0);

    windowbufAppend(winbufptr, movelocation, 8);
    switch (layout) {
        case PROMPT:
            windowbufAppend(winbufptr, "> ", 2);
            break;
        case EDITOR:
            windowbufAppend(winbufptr, "\x1b[38;5;245m> \x1b[0m", 17);
            break;
        default:
            break;
    }
}

void writeContent(WindowBuf *const winbufptr) {
}

void writeLineNumber(WindowBuf *const winbufptr, const u_int16_t row, const enum Layout layout) {
    char movelocation[8] = {'\0'};
    sprintf(movelocation, "\x1b[%d;%dH", layout == EDITOR ? 3 : 2, 0);

    windowbufAppend(winbufptr, movelocation, 8);

    for (int i = 0; i < row - (layout == EDITOR ? 4 : 3); i++) {
        windowbufAppend(winbufptr, "~\n\r", 3);
    }
}

void writePrompt(WindowBuf *const winbufptr, const Prompt *const promptptr, const u_int16_t col,
                 const u_int16_t row) {
    char movelocation[20] = {'\0'};
    sprintf(movelocation, "\x1b[%d;%dH", row, 3);
    windowbufAppend(winbufptr, movelocation, strlen(movel ocation));
    if (promptptr->len > col - 3) {
        windowbufAppend(winbufptr, "...", 3);
    } else {
        windowbufAppend(winbufptr, promptptr->ptr, promptptr->len);
    }
}
