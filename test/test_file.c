#include "error.h"
#include "handlers/file.h"
#include <assert.h>

void testOpenFile()
{
	const char* filename = "../test/SCRATCH.txt";
	const size_t len	 = strlen(filename);

	File* file = openFile(filename, len);

	assert(file != nullptr);
	assert(strncmp(filename, file->path.ptr, file->path.len) == 0);
	assert(strncmp("SCRATCH", file->filename.ptr, file->filename.len) == 0);
	assert(strncmp("txt", file->ext.ptr, file->ext.len) == 0);

	free(file);
}

void testParseCtx()
{
	// TODO
}

void testExtractExtension()
{
	RESET_ERROR;

	// TEST valid file extension
	auto filename = "../test/SCRATCH.txt";
	size_t len	  = strlen(filename);

	char* ext = extractExtension(filename, len);

	assert(Error.code == NOTSET);
	assert(ext != nullptr);
	assert(strlen(ext) == strlen("txt"));
	assert(strncmp(ext, "txt", strlen("txt")) == 0);

	free(ext);

	// TEST if . is the last char
	RESET_ERROR;
	filename = "../test/SCRATCH.";
	len		 = strlen(filename);

	ext = extractExtension(filename, len);

	assert(Error.code == NOTSET);
	assert(ext == nullptr);

	free(ext);

	// TEST filename without extension
	RESET_ERROR;
	filename = "../test/SCRATCH";
	len		 = strlen(filename);

	ext = extractExtension(filename, len);

	assert(Error.code == NOTSET);
	assert(ext == nullptr);

	free(ext);

	// TEST more than 8 extension character
	RESET_ERROR;
	filename = "../test/SCRATCH.isMoreThanEight";
	len		 = strlen(filename);

	ext = extractExtension(filename, len);

	assert(Error.code == NOTSET);
	assert(ext != nullptr);

	free(ext);
}

int main()
{

	// testOpenFile();
	// testExtractExtension();
	return 0;
}