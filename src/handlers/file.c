#include "handlers/file.h"

#include "error.h"

#include <stdio.h>

File* openFile(const char* file_path, const size_t len)
{
	File* file = malloc(sizeof(File));

	if (file == nullptr)
	{
		SET_ERROR_CODE(ERR_NULL_POINTER);
		return nullptr;
	}

	FILE* file_io = fopen(file_path, "rw");

	if (file_io == nullptr)
	{
		SET_ERROR_CODE(ERR_NULL_POINTER);
		return nullptr;
	}

	parseFileCtx(file, file_path, len);
	CATCH({ return nullptr; })

	file->file = file_io;
	return file;
}

void parseFileCtx(File* file, const char* file_path, size_t len)
{
	if (file == nullptr || file_path == nullptr)
	{
		SET_ERROR_CODE(ERR_NULL_POINTER);
		return;
	}

	if (len == 0)
	{
		SET_ERROR_CODE(PATH_ERR_INVALID_PATH);
		return;
	}

	file->ext.ptr = extractExtension(file_path, len);
	file->ext.len = strlen(file->ext.ptr);
	file->ext.cap = 8;
}

void readFile(const File* file) {}

char* extractFilename(const char* file_path, const size_t len) {}

char* extractExtension(const char* file_path, const size_t len)
{
	char* ext = calloc(8, sizeof(char)); // TODO dynamic ext size
	if (ext == nullptr)
	{
		SET_ERROR_CODE(ERR_NULL_POINTER);
		return nullptr;
	}
	size_t dot_position = len;

	for (; file_path[dot_position] != '.', dot_position > 0; dot_position--)
	{
		if (file_path[dot_position] == '/')
		{
			free(ext);
			return nullptr;
		}
	}

	dot_position++;

	if (dot_position == len - 8 || dot_position == len)
	{
		free(ext);
		return nullptr;
	}

	for (size_t ext_len = 0; ext_len <= 8, dot_position < len;
		 ext_len++, dot_position++)
	{
		ext[ext_len] = file_path[dot_position];
	}
	return ext;
}

void closeFile(const File* file)
{
	fclose(file->file);
}

void dropFile(const File* file)
{
	free(file->path.ptr);
	free(file->filename.ptr);
	free(file->ext.ptr);
}
