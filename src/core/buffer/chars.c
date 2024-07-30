#include "./chars.h"

Chars *charsCreate( UTF chr )
{
	Chars *ptr = ( Chars * )calloc( 1, sizeof( Chars ) );
	ptr->perv = NULL;
	ptr->chr = chr;
	ptr->next = NULL;
	return ptr;
}

Chars *charsConvertStringToChars( const UTF *ptr )
{
	Chars *firstcharptr, *charsptr;
	firstcharptr = charsptr = charsCreate( '\0' );
	for ( ;; ++ptr )
	{
		printf( "" );
	}
}
