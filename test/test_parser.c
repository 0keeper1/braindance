#include "cli/parser.h"

#include <assert.h>

void testIsFlagSuccess()
{
	constexpr char double_minus_flag[] = "--flag";
	constexpr char long_flag[]		   = "--long-flag-for-test";
	constexpr char single_minus_flag[] = "-f";

	bool ret = isFlag(double_minus_flag);
	assert(ret == true);

	ret = isFlag(single_minus_flag);
	assert(ret == true);

	ret = isFlag(long_flag);
	assert(ret == true);
}

void testIsFlagFailure()
{
	constexpr char space[]			  = " ";
	constexpr char empty[]			  = "";
	constexpr char characters[]		  = "ab";
	constexpr char three_minus_flag[] = "---flag";
	constexpr char two_minus_flag[]	  = "--";
	constexpr char minus_characters[] = "-a-";

	bool ret = isFlag(space);
	assert(ret == false);

	ret = isFlag(empty);
	assert(ret == false);

	ret = isFlag(characters);
	assert(ret == false);

	ret = isFlag(three_minus_flag);
	assert(ret == false);

	ret = isFlag(two_minus_flag);
	assert(ret == false);

	ret = isFlag(minus_characters);
	assert(ret == false);
}

int main()
{
	testIsFlagSuccess();
	testIsFlagFailure();

	return 0;
}
