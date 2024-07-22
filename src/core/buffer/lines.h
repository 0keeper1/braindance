#pragma once

#include "../../errors.h"
#include "../../settings.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>

struct Lines
{
	struct Lines *perv; // perv line
	int len;	    // content size
	UTF *ptr;	    // line characters convert to chars
	int cap;	    // allocated size
	struct Lines *next; // next line
};

typedef struct Lines Lines;

extern void linesClear( Lines *lineptr );

extern void linesDelete( Lines *lineptr );

extern void linesNewLine( Lines *lineptr );

extern Lines *linesCreate( UTF *contentptr, int cap, int len );

extern Lines *linesFileToLines( FILE *file );

extern Result linesClearAll( Lines *firstlineptr );

extern Result linesClearAllAndDrop( Lines *firtlineptr );

Lines *linesReachEnd( Lines *lineptr );

Result linesDrop( Lines *lineptr );
