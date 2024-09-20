#include "./core.h"

#include "../cmdline/cli.h"
#include "../errors.h"
#include "./buffer/lines.h"
#include "./buffer/windowbuf.h"
#include "./info.h"
#include "./offset.h"

#include <ctype.h>
#include <libgen.h>
#include <signal.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/ioctl.h>
#include <termios.h>
#include <unistd.h>


Core coreCreate() {
	const Core core = {
		.lines = NULL, .offset = offsetCreate(), .info = infoCreate(), .exit = false,
		.terminal = {.row = 0, .col = 0}
	};
	return core;
}

Result coreInit(Core *const coreptr, const Cmds *const cmdsptr) {
	if (enableRawMode(coreptr) == FAILED) {
		return FAILED;
	}

	if (coreTermSizeUpdate(coreptr) == FAILED) {
		return FAILED;
	}

	offsetLocationsUpdate(&coreptr->offset, coreptr->terminal.row, coreptr->terminal.col);

	coreptr->info.path = cmdsptr->path;
	coreptr->info.cwd = cmdsptr->cwd;

	return SUCCESSFUL;
}

Result coreLoop(const Cmds *const cmdsptr) {
	Core core = coreCreate();

	coreInit(&core, cmdsptr);

	do {
		// display(&core);
		// sleep(5);
		// keyProcess( &core );
		core.exit = true;
	} while (core.exit == false);

	coreExit(&core);

	return SUCCESSFUL;
}

void coreExit(Core *const coreptr) {
	disableRawMode(coreptr);

	infoFree(&coreptr->info); // double free detected here.

	linesFree(coreptr->lines);

	// write(STDOUT_FILENO, SCREEN_CLEAR, 4);
	// write(STDOUT_FILENO, CURSOR_AT_START, 3);
}

Result enableRawMode(Core *const coreptr) {
	struct termios rawterm;

	if (tcgetattr(STDIN_FILENO, &rawterm) < 0) {
		return FAILED;
	}

	coreptr->terminal.termio = rawterm;

	rawterm.c_iflag &= ~(BRKINT | ICRNL | INPCK | ISTRIP | IXON);
	rawterm.c_oflag &= ~(OPOST);
	rawterm.c_cflag |= (CS8);
	rawterm.c_lflag &= ~(ECHO | ICANON | IEXTEN | ISIG);
	rawterm.c_cc[VMIN] = 0;
	rawterm.c_cc[VTIME] = KEYBINDING_TIMOEOUT;

	if (tcsetattr(STDIN_FILENO, TCSAFLUSH, &rawterm) < 0) {
		return FAILED;
	}
	return SUCCESSFUL;
}

Result disableRawMode(const Core *const coreptr) {
	if (tcsetattr(STDIN_FILENO, TCSAFLUSH, &coreptr->terminal.termio) < 0) {
		return FAILED;
	}
	return SUCCESSFUL;
}

Result coreTermSizeUpdate(Core *const coreptr) {
	struct winsize WINSIZE;

	if (ioctl(STDOUT_FILENO, TIOCGWINSZ, &WINSIZE) > 0) {
		return FAILED;
	}

	coreptr->terminal.row = WINSIZE.ws_col;
	coreptr->terminal.col = WINSIZE.ws_row;

	return SUCCESSFUL;
}
