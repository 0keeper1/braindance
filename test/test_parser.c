#include "cli/parser.h"
#include "error.h"

#include <assert.h>
#include <string.h>

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

void testFlagCmp()
{
	constexpr char long_flag[]			= "--flag";
	constexpr char small_flag[]			= "-f";
	constexpr char invalid_long_flag[]	= "-ff-flag";
	constexpr char invalid_small_flag[] = "--flagdad";

	bool ret = flagCmp(small_flag, "-f", "--flag");
	assert(ret == true);
	ret = flagCmp(long_flag, "-f", "--flag");
	assert(ret == true);

	ret = flagCmp(invalid_small_flag, "-f", "--flag");
	assert(ret == false);
	ret = flagCmp(invalid_long_flag, "-f", "--flag");
	assert(ret == false);
}

void testArgParse()
{
	Args args		  = {.version = false,
						 .help	  = false,
						 .cwd	  = {.cap = 0, .len = 0, .ptr = nullptr},
						 .path	  = {.cap = 0, .len = 0, .ptr = nullptr}};
	int argc		  = 1;
	char* cwd_argv[5] = {"/bin/sh"};

	memset(&args, 0, sizeof(Args));
	parseArgs(&args, argc, cwd_argv);

	assert(args.version == false && args.help == false);
	assert(strncmp(args.cwd.ptr, cwd_argv[0], strlen(cwd_argv[0])) == 0 &&
		   strlen(cwd_argv[0]) == args.cwd.len);
	assert((args.path.ptr == nullptr) && (args.path.len == 0));

	argc			  = 2;
	char* help_argv[] = {"/bin/sh", "-h"};

	memset(&args, 0, sizeof(Args));
	parseArgs(&args, argc, help_argv);

	assert(args.version == false && args.help == true);
	assert(args.path.ptr == nullptr && args.path.len == 0);
	assert(strncmp(args.cwd.ptr, cwd_argv[0], strlen(cwd_argv[0])) == 0 &&
		   strlen(cwd_argv[0]) == args.cwd.len);

	argc			  = 3;
	char* full_argv[] = {"/bin/sh", "-v", "../folder/something.c"};

	memset(&args, 0, sizeof(Args));
	parseArgs(&args, argc, full_argv);

	assert(args.version == true && args.help == false);
	assert(strncmp(args.cwd.ptr, cwd_argv[0], strlen(cwd_argv[0])) == 0 &&
		   strlen(cwd_argv[0]) == args.cwd.len);

	char* real_path = malloc(50 * sizeof(char));
	realpath("../LICENSE", real_path);
	assert(strncmp(args.path.ptr, real_path, args.path.len) == 0);
	free(real_path);

	argc				  = 5;
	char* too_many_argv[] = {
		"/bin/sh", "-v", "../folder/something.c", "awd", "dawpokdawp"};

	memset(&args, 0, sizeof(Args));
	parseArgs(&args, argc, too_many_argv);

	assert(Error.code == CLI_ERR_TOO_MANY_ARGUMENTS);
}

int main()
{
	testIsFlagSuccess();
	testIsFlagFailure();
	testFlagCmp();
	testArgParse();
	return 0;
}
