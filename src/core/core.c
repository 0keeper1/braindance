#include "./core.h"

Result coreCreate(Core *const coreptr) {
	Info info;
	if (infoCreate(&info) != SUCCESSFUL) {
		return OUT_OF_MEMORY;
	}
	coreptr->offset = offsetCreate();
	coreptr->lines = NULL;

	return SUCCESSFUL;
}

Result coreInit(Core *const coreptr, const Cmds *const cmdsptr) {
	winsizeUpdate();

	enableRawMode();

	offsetLocationsUpdate(&coreptr->offset);

	coreptr->lines = NULL;

	coreptr->info.path = cmdsptr->path;
	coreptr->info.cwd = cmdsptr->cwd;
	coreptr->info.name = NULL;
	coreptr->info.ext = NULL;

	return SUCCESSFUL;
}

Result coreLoop(const Cmds *const cmdsptr) {
	Core core;

	if (coreCreate(&core) != SUCCESSFUL) {
		return FAILED;
	}

	coreInit(&core, cmdsptr);

	do {
		display(&core);
		sleep(5);
		// keyProcess( &core );
		// core.exit = true;
	} while (core.exit == false);

	coreExit(&core);

	return SUCCESSFUL;
}

void coreExit(Core *const coreptr) {
	disableRawMode();

	infoFree(&coreptr->info); // double free detected here.

	linesFree(coreptr->lines);

	write(STDOUT_FILENO, SCREEN_CLEAR, 4);
	write(STDOUT_FILENO, CURSOR_AT_START, 3);
}

Result enableRawMode() {
	struct termios rawterm;

	if (tcgetattr(STDIN_FILENO, &rawterm) < 0) {
		return FAILED;
	}

	ORGTERMIOS = rawterm;

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

Result disableRawMode() {
	if (tcsetattr(STDIN_FILENO, TCSAFLUSH, &ORGTERMIOS) < 0) {
		return FAILED;
	}
	return SUCCESSFUL;
}
