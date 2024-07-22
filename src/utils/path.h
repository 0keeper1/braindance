#pragma once

#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

enum PathError
{
	P_IS_VALID,
	P_INVALID,
	P_IS_DIR,
	P_IS_FILE,
	P_INVALID_CHAR,
	P_PATH_IS_NULL,
	P_CWD_IS_NULL,
	P_IO,
	P_DOES_NOT_EXISTS,
	P_PERM_DENIED,
};

enum PathError checkPath( const char *const cwd, const char *const path );

bool isPath( const char *path );
