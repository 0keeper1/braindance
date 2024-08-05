#include "./chars.h"

Chars *charsCreate( UTF chr )
{
	Chars *ptr = ( Chars * )calloc( 1, sizeof( Chars ) );
	ptr->perv = NULL;
	ptr->chr = chr;
	ptr->next = NULL;
	return ptr;
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

void test_charsCreate()
{
	Chars *character = charsCreate( 'A' );
	NANO_ASSERT_EQ_CHAR( "check chr", 'A', character->chr );
	free( character );
}

void test_charsConvertStringToChars()
{
	UTF *content = ( UTF * )calloc( 80, sizeof( UTF ) );
	memcpy( content, "Hello, World!\n", 14 );
	Chars *chars = charsConvertStringToChars( content, 14 );
	for ( int index = 0; index < 14 && chars != NULL; index++, chars = chars->next )
	{
		NANO_ASSERT_EQ_CHAR( "check chr", content[index], chars->chr );
	}
}

int main()
{
	NANO_SINGLE_TEST( test_charsCreate );
	NANO_SINGLE_TEST( test_charsConvertStringToChars );
	return 0;
}
#endif