#include "./lines.h"

void linesClear(Lines *lineptr) {
	free(lineptr->content);
	lineptr->content = nullptr;
	lineptr->cap = 0;
	lineptr->len = 0;
}

Result linesClearAll(Lines *lineptr) {
	for (; lineptr->next != nullptr; ++lineptr) {
		free(lineptr->content);
		lineptr->cap = 0;
		lineptr->len = 0;
	}

	return SUCCESSFUL;
}

Result linesDrop(Lines *lineptr) {
	if (lineptr->content != nullptr && lineptr->cap != 0 && lineptr->len != 0) {
		return FAILED;
	}
	free(lineptr);
	return SUCCESSFUL;
}

Lines *linesReachEnd(Lines *lineptr) {
	for (; lineptr != nullptr; lineptr++) {
	}
	return lineptr;
}

Result linesFree(const Lines *lineptr) {
	if (lineptr == nullptr) {
		return SUCCESSFUL;
	};
	// TODO recursive free the lines
	return SUCCESSFUL;
}

Lines *linesCreate(char *contentptr, const int cap, const int len) {
	if (len > cap) {
		return nullptr;
	}

	Lines *lineptr = calloc(1, sizeof(Lines));

	lineptr->perv = nullptr;
	lineptr->content = contentptr;

	if (contentptr == nullptr) {
		lineptr->cap = 0;
		lineptr->len = 0;
	} else {
		lineptr->cap = cap;
		lineptr->len = len;
	}

	lineptr->next = nullptr;
	return lineptr;
}

void linesSetContentPtr(Lines *lineptr, char *contentptr, const int cap, const int len) {
	lineptr->cap = cap;
	lineptr->len = len;
	lineptr->content = contentptr;
}

void linesClearAndDrop(Lines *lineptr) {
	free(lineptr->content);
	free(lineptr);
}

void linesDelete(Lines *lineptr) {
	Lines *tmpnext = lineptr->next;
	Lines *tmpperv = lineptr->perv;

	if (tmpnext != nullptr) {
		tmpnext->perv = tmpperv;
	}

	if (tmpperv != nullptr) {
		tmpperv->next = tmpnext;
	}

	free(lineptr->content); // remove line content
	free(lineptr); // remove line from heap
}

char *linesContentCreate(int cap) { return (char *) calloc(cap, sizeof(char)); }

void linesNewLine(Lines *lineptr) {
	Lines *newlineptr = linesCreate(nullptr, 0, 0);

	lineptr->next = newlineptr;
	newlineptr->perv = lineptr;
}

Lines *linesFileToLines(char *const pathptr) {
	int chr;
	FILE *fileptr;
	if ((fileptr = fopen((char *) pathptr, "r+")) == nullptr) {
		return nullptr;
	}

	Lines *lineptr, *pervlineptr = nullptr;
	char utfchr, *contentptr = nullptr;

	int len = 0;
	int cap = DEFAULT_ALLOCATION_SIZE_PER_LINE;

	contentptr = linesContentCreate(cap);
	Lines *const firstlinesptr = lineptr = linesCreate(contentptr, cap, len);

	if (firstlinesptr == nullptr) {
		free(contentptr);
		return nullptr;
	}

	while ((chr = fgetc(fileptr)) != EOF) {
		utfchr = (char) chr;
		if (len > cap) {
			contentptr =
					(char *) realloc(contentptr, (cap + REALLOCATE_SIZE_TO_INCREASE_CAP) * sizeof(char));
			cap += 20;
		}

		contentptr[len] = utfchr;
		len++;
		if (utfchr == '\n') {
			{
				lineptr->perv = pervlineptr;
				linesSetContentPtr(lineptr, contentptr, cap, len);
				pervlineptr = lineptr;
			}

			len = 0;
			cap = DEFAULT_ALLOCATION_SIZE_PER_LINE;
			contentptr = linesContentCreate(cap);
			lineptr = linesCreate(contentptr, cap, len);

			if (lineptr == nullptr) {
				free(contentptr);
				return nullptr;
			} {
				lineptr->perv = pervlineptr;
				pervlineptr->next = lineptr;
			}
		}
	}

	return firstlinesptr;
}
