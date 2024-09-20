#include "./lines.h"

void linesClear(Lines *lineptr) {
	free(lineptr->content);
	lineptr->content = NULL;
	lineptr->cap = 0;
	lineptr->len = 0;
}

Result linesClearAll(Lines *lineptr) {
	for (; lineptr->next != NULL; ++lineptr) {
		free(lineptr->content);
		lineptr->cap = 0;
		lineptr->len = 0;
	}

	return SUCCESSFUL;
}

Result linesDrop(Lines *lineptr) {
	if (lineptr->content != NULL && lineptr->cap != 0 && lineptr->len != 0) {
		return FAILED;
	}
	free(lineptr);
	return SUCCESSFUL;
}

Lines *linesReachEnd(Lines *lineptr) {
	for (; lineptr != NULL; lineptr++) {
	}
	return lineptr;
}

Result linesFree(const Lines *lineptr) {
	if (lineptr == NULL) {
		return SUCCESSFUL;
	};
	// TODO recursive free the lines
	return SUCCESSFUL;
}

Lines *linesCreate(char *contentptr, const int cap, const int len) {
	if (len > cap) {
		return NULL;
	}

	Lines *lineptr = calloc(1, sizeof(Lines));

	lineptr->perv = NULL;
	lineptr->content = contentptr;

	if (contentptr == NULL) {
		lineptr->cap = 0;
		lineptr->len = 0;
	} else {
		lineptr->cap = cap;
		lineptr->len = len;
	}

	lineptr->next = NULL;
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

	if (tmpnext != NULL) {
		tmpnext->perv = tmpperv;
	}

	if (tmpperv != NULL) {
		tmpperv->next = tmpnext;
	}

	free(lineptr->content); // remove line content
	free(lineptr); // remove line from heap
}

char *linesContentCreate(int cap) { return (char *) calloc(cap, sizeof(char)); }

void linesNewLine(Lines *lineptr) {
	Lines *newlineptr = linesCreate(NULL, 0, 0);

	lineptr->next = newlineptr;
	newlineptr->perv = lineptr;
}

Lines *linesFileToLines(char *const pathptr) {
	int chr;
	FILE *fileptr;
	if ((fileptr = fopen((char *) pathptr, "r+")) == NULL) {
		return NULL;
	}

	Lines *lineptr, *pervlineptr = NULL;
	char utfchr, *contentptr = NULL;

	int len = 0;
	int cap = DEFAULT_ALLOCATION_SIZE_PER_LINE;

	contentptr = linesContentCreate(cap);
	Lines *const firstlinesptr = lineptr = linesCreate(contentptr, cap, len);

	if (firstlinesptr == NULL) {
		free(contentptr);
		return NULL;
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

			if (lineptr == NULL) {
				free(contentptr);
				return NULL;
			} {
				lineptr->perv = pervlineptr;
				pervlineptr->next = lineptr;
			}
		}
	}

	return firstlinesptr;
}
