#include <nanotest/lib.h>

NANO_FUNCTION(something_tst, true, {
	NANO_ASSERT_TRUE("they are all true?", true, true);
	NANO_ASSERT_EQ_INT("they are all the same?", 1, 1, true);
})

NANO_MAIN({
	NANO_GROUP_TEST("Adwad", something_tst, something_tst, );
	NANO_SINGLE_TEST(something_tst);
})
