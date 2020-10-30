
#ifndef COMMON_BOOL_H
#define COMMON_BOOL_H

/* From "version.h" */

#define C99_VERSION_VALUE 199901L

#if !defined(__STDC_VERSION__) || __STDC_VERSION__ <= C99_VERSION_VALUE
#define _Bool unsigned char
#endif

#include <stdbool.h>

#undef CC99_VERSION_VALUE

#endif