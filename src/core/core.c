#include <ctype.h>
#include <sys/ioctl.h>
#include <termios.h>
#include <unistd.h>

#include "core/core.h"
#include "cmdline/cli.h"
#include "errors.h"
#include "core/info.h"
#include "core/offset.h"
#include "core/display/update.h"
#include "core/buffer/prompt.h"
#include "core/input.h"

Core coreCreate() {
	const Core core = {
		.lines = nullptr,
		.offset = offsetCreate(),
		.info = infoCreate(),
		.exit = false,
		.prompt = promptCreate(),
		.skip = false,
		.layout = PROMPT,
		.terminal = {
			.row = 0,
			.col = 0,
			.termio = {
				0
			}
		}
	};
	return core;
}

Result coreInit(Core *const core_ptr, const Cmds *const cmds_ptr) {
	if (enableRawMode(core_ptr) == FAILED) {
		return FAILED;
	}

	if (coreTermSizeUpdate(core_ptr) == FAILED) {
		return FAILED;
	}

	core_ptr->offset.cursor.poscol = 1;
	core_ptr->offset.cursor.posrow = 2;
	core_ptr->info.path = cmds_ptr->path;
	core_ptr->info.cwd = cmds_ptr->cwd;

	return SUCCESSFUL;
}

Result coreLoop(const Cmds *const cmds_ptr) {
	Core core = coreCreate();

	coreInit(&core, cmds_ptr);

	display(&core);

	do {
		keyProcess(&core);
		if (core.skip == true) {
			core.skip = false;
			continue;
		}
		display(&core);
	} while (core.exit == false);

	coreExit(&core);

	return SUCCESSFUL;
}

void coreExit(const Core *const core_ptr) {
	disableRawMode(core_ptr);

	infoFree(&core_ptr->info);

	// linesFree(coreptr->lines); TODO replace

	write(STDOUT_FILENO, SCREEN_CLEAR, 4);
	write(STDOUT_FILENO, CURSOR_AT_START, 3);
}

Result enableRawMode(Core *const core_ptr) {
	struct termios raw_term;

	if (tcgetattr(STDIN_FILENO, &raw_term) < 0) {
		return FAILED;
	}

	core_ptr->terminal.termio = raw_term;

	raw_term.c_iflag &= ~(BRKINT | ICRNL | INPCK | ISTRIP | IXON);
	raw_term.c_oflag &= ~(OPOST);
	raw_term.c_cflag |= (CS8);
	raw_term.c_lflag &= ~(ECHO | ICANON | IEXTEN | ISIG);
	raw_term.c_cc[VMIN] = 0;
	raw_term.c_cc[VTIME] = KEYBINDING_TIMOEOUT;

	if (tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw_term) < 0) {
		return FAILED;
	}
	return SUCCESSFUL;
}

Result disableRawMode(const Core *const core_ptr) {
	if (tcsetattr(STDIN_FILENO, TCSAFLUSH, &core_ptr->terminal.termio) < 0) {
		return FAILED;
	}
	return SUCCESSFUL;
}

Result coreTermSizeUpdate(Core *const core_ptr) {
	struct winsize WINSIZE;

	if (ioctl(STDOUT_FILENO, TIOCGWINSZ, &WINSIZE) > 0) {
		return FAILED;
	}

	core_ptr->terminal.col = WINSIZE.ws_col;
	core_ptr->terminal.row = WINSIZE.ws_row;

	return SUCCESSFUL;
}
