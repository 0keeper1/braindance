#pragma once

#include "macros.h"
#include <stdio.h>

typedef struct File
{
	FILE* file;
	STRING(path);
	STRING(filename);
	STRING(ext);
} File;

extern File* openFile(const char* file_path,
					  size_t len); // TODO just Open the file

extern void readFile(const File* file); // TODO read file Content

extern void writeFile(File* file,
					  char* data); // TODO char pointer or Lines pointer?

char* extractFilename(const char* file_path, const size_t len);

char* extractExtension(const char* file_path, const size_t len);

void parseFileCtx(File* file,
				  const char* file_path,
				  size_t len); // TODO parse file name path and ext

extern void closeFile(const File* file);

extern void dropFile(const File* restrict file);
