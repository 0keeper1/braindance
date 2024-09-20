#include "./update.h"

Result display(Core *const coreptr) {
	// TODO add window buf allocation here
	WindowBuf winbuf;
	windowbufCreate(&winbuf);
	windowbufResize(&winbuf);

	windowbufAppend(&winbuf, SCREEN_CLEAR, 4);

	writeHeaderBar(&winbuf);
	// writeFooterBar( coreptr );
	// writeContent( coreptr );
	// writeSideBars( coreptr );
	// writeCommandBar( coreptr );

	windowbufWrite(&winbuf);

	return SUCCESSFUL;
}
