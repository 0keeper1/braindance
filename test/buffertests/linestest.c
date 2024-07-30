#include "./linestest.h"

void test_linesCreate()
{
	Lines *line = linesCreate( NULL, 0, 0 );
	NANO_ASSERT_EQ_INT( "line cap", 0, line->cap );
	NANO_ASSERT_EQ_INT( "line len", 0, line->len );
	NANO_ASSERT_EQ_PTR( "line content", NULL, line->ptr );
	NANO_ASSERT_EQ_PTR( "line next", NULL, line->next );
	NANO_ASSERT_EQ_PTR( "line perv", NULL, line->perv );

	free( line );
}

void test_lineModifie()
{
	Lines *lineperv = linesCreate( NULL, 0, 0 );
	Lines *line = linesCreate( NULL, 0, 0 );
	Lines *linenext = linesCreate( NULL, 0, 0 );
	line->next = linenext;
	line->perv = lineperv;
}

void test_lines() { NANO_GROUP_TEST( "Lines", test_linesCreate ); }