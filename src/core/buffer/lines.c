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
		printf( "%s", endoflinesptr->ptr );
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

void linesSetContentPtr( Lines *lineptr, UTF *contentptr, int cap, int len )
{
	lineptr->cap = cap;
	lineptr->len = len;
	lineptr->ptr = contentptr;
}

void linesClearAndDrop( Lines *lineptr )
{
	free( lineptr->ptr );
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

	free( lineptr->ptr ); // remove line content
	free( lineptr );      // remove line from heap
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
	Lines *firstlinesptr, *lineptr, *pervlineptr = NULL;
	UTF utfchr, *contentptr = NULL;

	len = 0;
	cap = DEFAULT_ALLOCATION_SIZE_PER_LINE;

	contentptr = linesContentCreate( cap );
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

#ifdef TEST

	#include "nanotest/src/lib.h"

void test_linesCreate()
{
	Lines *line = linesCreate( NULL, 0, 0 );
	NANO_ASSERT_EQ_PTR( "eq next", NULL, line->next );
	NANO_ASSERT_EQ_INT( "eq cap", 0, line->cap );
	NANO_ASSERT_EQ_PTR( "eq ptr", NULL, line->ptr );
	NANO_ASSERT_EQ_INT( "eq len", 0, line->len );
	NANO_ASSERT_EQ_PTR( "eq perv", NULL, line->perv );
}

void test_lBCLines()
{
	Lines *line = linesCreate( NULL, 20, 32 );
	NANO_ASSERT_EQ_PTR( "eq line", NULL, line );
}

void test_linesSetContentPtr()
{
	UTF *ptr = ( UTF * )calloc( 20, sizeof( UTF ) );
	Lines *line = linesCreate( NULL, 0, 0 );
	linesSetContentPtr( line, ptr, 20, 0 );
	NANO_ASSERT_EQ_PTR( "eq ptr", ptr, line->ptr );
	NANO_ASSERT_EQ_INT( "eq cap", 20, line->cap );
}

void test_linesNewLine()
{
	Lines *line = linesCreate( NULL, 0, 0 );
	linesNewLine( line );
	Lines *pervline = line->next;
	NANO_ASSERT_NOTEQ_PTR( "not eq next", NULL, line->next );
	NANO_ASSERT_EQ_PTR( "perv memeber of new line", line, pervline->perv );
}

void test_linesDelete()
{
	Lines *line1 = linesCreate( NULL, 0, 0 );
	Lines *line2 = linesCreate( NULL, 0, 0 );
	Lines *line3 = linesCreate( NULL, 0, 0 );

	line1->next = line2;
	line2->perv = line1;
	line2->next = line3;
	line3->perv = line2;

	linesDelete( line2 );

	NANO_ASSERT_EQ_PTR( "check line1 next", line3, line1->next );
	NANO_ASSERT_EQ_PTR( "check line3 perv", line1, line3->perv );
}

int main()
{
	NANO_SINGLE_TEST( test_linesCreate );
	NANO_SINGLE_TEST( test_linesSetContentPtr );
	NANO_SINGLE_TEST( test_linesNewLine );
	NANO_SINGLE_TEST( test_linesDelete );

	NANO_SINGLE_TEST( test_lBCLines );
	return 0;
}
#endif