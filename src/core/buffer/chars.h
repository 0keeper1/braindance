#pragma once

#include "../../errors.h"
#include "../../settings.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>

struct Chars
{
	struct Chars *perv;
	UTF chr;
	struct Chars *next;
};

typedef struct Chars Chars;

extern Chars *charsConvertStringToChars( const UTF *ptr, int len );
extern Chars *charsCreate( UTF chr );
extern void charsRemoveChar( Chars *chrptr );
extern inline void charsFree( Chars *chrptr );
