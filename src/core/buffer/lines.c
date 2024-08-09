#include "./lines.h"

void linesClear( Lines *lineptr )
{
	free( lineptr->content );
	lineptr->content = NULL;
	lineptr->cap = 0;
	lineptr->len = 0;
}

Result linesClearAll( Lines *firstlineptr )
{
	for ( ; firstlineptr->next != NULL; ++firstlineptr )
	{
		free( firstlineptr->content );
		firstlineptr->cap = 0;
		firstlineptr->len = 0;
	}

	return SUCCESSFUL;
}

Result linesDrop( Lines *lineptr )
{
	if ( lineptr->content != NULL && lineptr->cap != 0 && lineptr->len != 0 )
	{
		return FAILED;
	}
	free( lineptr );
	return SUCCESSFUL;
}

Lines *linesReachEnd( Lines *lineptr )
{
	for ( ; lineptr != NULL; lineptr++ )
	{
	}
	return lineptr;
}

Result linesClearAllAndDrop( Lines *firtlineptr )
{
	Lines *endoflinesptr;
	endoflinesptr = linesReachEnd( firtlineptr );
	for ( ; endoflinesptr != NULL; endoflinesptr = endoflinesptr->perv )
	{
		printf( "%s", endoflinesptr->content );
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
	lineptr->content = contentptr;

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

void linesSetContentPtr( Lines *lineptr, UTF *contentptr, int cap, int len )
{
	lineptr->cap = cap;
	lineptr->len = len;
	lineptr->content = contentptr;
}

void linesClearAndDrop( Lines *lineptr )
{
	free( lineptr->content );
	free( lineptr );
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

	free( lineptr->content ); // remove line content
	free( lineptr );	  // remove line from heap
}

inline UTF *linesContentCreate( int cap ) { return ( UTF * )calloc( cap, sizeof( UTF ) ); }

void linesNewLine( Lines *lineptr )
{
	Lines *newlineptr;

	newlineptr = linesCreate( NULL, 0, 0 );

	lineptr->next = newlineptr;
	newlineptr->perv = lineptr;
}

Lines *linesFileToLines( FILE *fileptr )
{
	int chr, len, cap;
	Lines *lineptr, *pervlineptr = NULL;
	UTF utfchr, *contentptr = NULL;

	len = 0;
	cap = DEFAULT_ALLOCATION_SIZE_PER_LINE;

	contentptr = linesContentCreate( cap );
	Lines *const firstlinesptr = lineptr = linesCreate( contentptr, cap, len );

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
			contentptr = realloc( contentptr, ( cap + REALLOCATE_SIZE_TO_INCREASE_CAP ) * sizeof( UTF ) );
			cap += 20;
		}

		contentptr[len] = utfchr;
		len++;
		if ( utfchr == '\n' )
		{

			{
				lineptr->perv = pervlineptr;
				linesSetContentPtr( lineptr, contentptr, cap, len );
				pervlineptr = lineptr;
			}

			len = 0;
			cap = DEFAULT_ALLOCATION_SIZE_PER_LINE;
			contentptr = linesContentCreate( cap );
			lineptr = linesCreate( contentptr, cap, len );

			if ( lineptr == NULL )
			{
				free( contentptr );
				return NULL;
			}

			{
				lineptr->perv = pervlineptr;
				pervlineptr->next = lineptr;
			}
		}
	}

	return firstlinesptr;
}
