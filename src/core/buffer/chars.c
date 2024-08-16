#include "./chars.h"

Chars *charsCreate( UTF chr )
{
	Chars *ptr = ( Chars * )calloc( 1, sizeof( Chars ) );
	ptr->perv = NULL;
	ptr->chr = chr;
	ptr->next = NULL;
	return ptr;
}

void charsFree( Chars *chrptr ) { free( chrptr ); }

void charsRemoveChar( Chars *const chrptr )
{
	Chars *tmpperv = chrptr->perv;
	Chars *tmpnext = chrptr->next;
	if ( tmpnext != NULL )
	{
		tmpnext->perv = tmpperv;
	}
	if ( tmpperv != NULL )
	{
		tmpperv->next = tmpnext;
	}
	charsFree( chrptr );
}

void charsInsertChar( Chars *const chrptr, const UTF newchar )
{
	Chars *newcharsptr = charsCreate( newchar );
	newcharsptr->perv = chrptr;
	newcharsptr->next = chrptr->next;
	chrptr->next = newcharsptr;
}

Chars *charsConvertStringToChars( const UTF *ptr, int len )
{
	Chars *charsptr, *pervcharptr = NULL;
	Chars *const firstcharptr = charsptr = charsCreate( '\0' );
	for ( int i = 0; i < len; ++i )
	{
		charsptr->chr = ptr[i];
		pervcharptr = charsptr;
		charsptr = charsCreate( '\0' );
		charsptr->perv = pervcharptr;
		pervcharptr->next = charsptr;
	}
	return firstcharptr;
}

#ifdef TEST

	#include "nanotest/src/lib.h"

int main()
{
	Chars *chrptr = charsCreate( 'H' );
	charsInsertChar( chrptr, 'e' );
	chrptr = chrptr->next;
	charsRemoveChar( chrptr->perv );
	for ( ; chrptr != NULL; chrptr = chrptr->next )
	{
		printf( "%c", chrptr->chr );
	}
	return 0;
}
#endif