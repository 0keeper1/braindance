#include "./lines.h"

void linesClear( Lines *lineptr )
{
	free( lineptr->ptr );
	lineptr->ptr = NULL;
	lineptr->cap = 0;
	lineptr->len = 0;
}

Result linesClearAll( Lines *firstlineptr )
{
	for ( ; firstlineptr->next != NULL; ++firstlineptr )
	{
		free( firstlineptr->ptr );
		firstlineptr->cap = 0;
		firstlineptr->len = 0;
	}

	return SUCCESSFUL;
}

Result linesDrop( Lines *lineptr )
{
	if ( lineptr->ptr != NULL && lineptr->cap != 0 && lineptr->len != 0 )
	{
		return FAILED;
	}
	free( lineptr );
	return SUCCESSFUL;
}

Lines *linesReachEnd( Lines *lineptr )
{
	for ( ; lineptr->next != NULL; lineptr++ )
	{
	}
	return lineptr;
}

Result linesClearAllAndDrop( Lines *firtlineptr )
{
	Lines *endoflinesptr;
	endoflinesptr = linesReachEnd( firtlineptr );
	for ( ; endoflinesptr->perv != NULL; --endoflinesptr )
	{
		linesClear( endoflinesptr );
	}
	return SUCCESSFUL;
}

Lines *linesCreate( UTF *contentptr, int cap, int len )
{
	Lines *lineptr;

	if ( len > cap )
	{
		return NULL;
	}

	lineptr = ( Lines * )calloc( 1, sizeof( Lines ) );

	lineptr->perv = NULL;
	lineptr->ptr = contentptr;

	if ( contentptr == NULL )
	{
		lineptr->cap = 0;
		lineptr->len = 0;
	}
	else
	{
		lineptr->cap = cap;
		lineptr->len = len;
	}

	lineptr->next = NULL;
	return lineptr;
}

void linesDelete( Lines *lineptr )
{
	Lines *tmpperv;
	Lines *tmpnext;

	tmpnext = lineptr->next;
	tmpperv = lineptr->perv;

	if ( tmpnext != NULL )
	{
		tmpnext->perv = tmpperv;
	}

	if ( tmpperv != NULL )
	{
		tmpperv->next = tmpnext;
	}

	linesClear( lineptr ); // remove line content
	free( lineptr );       // remove line from heap
}

void linesNewLine( Lines *lineptr )
{
	Lines *tmpnext;
	Lines *newlineptr;

	tmpnext = lineptr->next;
	newlineptr = linesCreate( NULL, 0, 0 );

	lineptr->next = newlineptr;
	newlineptr->perv = lineptr;
	newlineptr->next = tmpnext;
	tmpnext->perv = newlineptr;
}

Lines *linesFileToLines( FILE *fileptr )
{
	int chr, len, cap;
	Lines *firstlinesptr, *lineptr, *pervlineptr = NULL;
	UTF utfchr, *contentptr = NULL;

	len = 0;
	cap = DEFAULT_ALLOCATION_SIZE_PER_LINE;

	contentptr = ( UTF * )calloc( cap, sizeof( UTF ) );
	firstlinesptr = lineptr = linesCreate( contentptr, cap, len );

	if ( firstlinesptr == NULL )
	{
		free( contentptr );
		return NULL;
	}

	while ( ( chr = fgetc( fileptr ) ) != EOF )
	{
		utfchr = ( UTF )chr;

		if ( len > cap )
		{
			contentptr = realloc( contentptr, ( cap + 20 ) * sizeof( UTF ) );
			cap += 20;
		}

		contentptr[len] = utfchr;
		len++;
		if ( utfchr == '\n' )
		{

			// set values to current line
			{
				lineptr->perv = pervlineptr;
				lineptr->cap = cap;
				lineptr->ptr = contentptr;
				lineptr->len = len;
				// save current line as perv
				pervlineptr = lineptr;
			}

			len = 0;
			cap = DEFAULT_ALLOCATION_SIZE_PER_LINE;
			contentptr = ( UTF * )calloc( cap, sizeof( UTF ) );
			lineptr = linesCreate( contentptr, cap, len );

			if ( lineptr == NULL )
			{
				free( contentptr );
				return NULL;
			}

			// set next and perv
			{
				lineptr->perv = pervlineptr;
				pervlineptr->next = lineptr;
			}
		}
	}

	return firstlinesptr;
}
