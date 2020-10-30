/*
 *  _____      _ _ __  __
 * |  ___|   _| | |  \/  | __ _  ___ _ __ ___
 * | |_ | | | | | | |\/| |/ _` |/ __| '__/ _ \
 * |  _|| |_| | | | |  | | (_| | (__| | | (_) |
 * |_|   \__,_|_|_|_|  |_|\__,_|\___|_|  \___/
 *
 * Heretic C and nothing else.
 */

/* Section 1: Version Checking */

#ifndef FULL_MACRO_H
#define FULL_MACRO_H

#include <stdio.h>

/* This little excerpt is  from version.h */

#define C11_VERSION_VALUE 201112L

#if !defined(__STDC_VERSION__) || __STDC_VERSION__ < C11_VERSION_VALUE

#error The C11 standard is required to use the Full Macro Header

#endif /* __STDC_VERSION < C11_VERSION_VALUE */

#undef C11_VERSION_VALUE

#ifdef __cplusplus

#error The usage of FullMacro with C++ is prohibited.

#endif /* __cplusplus */


/* Section 2: Inner Macros */

/* TODO: Check if const part is needed and remove it if so */

#define __full_macro_get_type_specifier_of(x) \
    _Generic((x)                    ,         \
        char                   : "%c"   , const char                   : "%c"   , \
        signed char            : "%hhc" , const signed char            : "%hhc" , \
        unsigned char          : "%hhu" , const unsigned char          : "%hhu" , \
        int                    : "%d"   , const int                    : "%d"   , \
        unsigned int           : "%u"   , const unsigned int           : "%u"   , \
        short int              : "%hd"  , const short int              : "%hd"  , \
        unsigned short int     : "%hu"  , const unsigned short int     : "%hu"  , \
        long int               : "%ld"  , const long int               : "%ld"  , \
        long long int          : "%lld" , const long long int          : "%lld" , \
        unsigned long long int : "%llu" , const unsigned long long int : "%llu" , \
        unsigned long int      : "%lu"  , const unsigned long int      : "%lu"  , \
        _Bool                  : "%d"   , const _Bool                  : "%d"   , \
        long double            : "%Lf"  , const long double            : "%Lf"  , \
        double                 : "%.2f" , const double                 : "%.2f" , \
        float                  : "%.2f" , const float                  : "%.2f" , \
        char*                  : "%s"   , const char*                  : "%s"   , \
        const char* const      : "%s",                                            \
        void*                  : "%p"   , const void*                  : "%p",    \
        const void* const      : "%p"                                             \
    )

#ifndef FULL_MACRO_EXTENDED_TYPENAMES
#define FULL_MACRO_EXTENDED_TYPENAMES
#endif

/* I don't create inner macros for the EXTEND ones because they don't expand too much */

/**
 * Registers a single type in `typename_of`.
 */
#define FULL_MACRO_EXTEND(type) , type: #type

/**
 * Registers a given type, the pointer to given type, and the const pointer to the type in
 * `typename_of`
 */
#define FULL_MACRO_COMPLETE_EXTEND(type) \
    , type: #type \
    , type *: #type " *", const type *: "const " #type " *"

/**
 * The macro used to register the builtin types of the `typename_of` macro.
 */
#ifndef FULL_MACRO_INNER_EXTENSOR
#define FULL_MACRO_INNER_EXTENSOR FULL_MACRO_COMPLETE_EXTEND
#endif


#define __full_macro_typename_of(x) \
    (char*) _Generic((x)\
        FULL_MACRO_INNER_EXTENSOR(char) \
        FULL_MACRO_INNER_EXTENSOR(signed char) \
        FULL_MACRO_INNER_EXTENSOR(unsigned char) \
        FULL_MACRO_INNER_EXTENSOR(int) \
        FULL_MACRO_INNER_EXTENSOR(unsigned int) \
        FULL_MACRO_INNER_EXTENSOR(short) \
        FULL_MACRO_INNER_EXTENSOR(unsigned short) \
        FULL_MACRO_INNER_EXTENSOR(long) \
        FULL_MACRO_INNER_EXTENSOR(unsigned long) \
        FULL_MACRO_INNER_EXTENSOR(long long) \
        FULL_MACRO_INNER_EXTENSOR(unsigned long long) \
        FULL_MACRO_INNER_EXTENSOR(long double) \
        FULL_MACRO_INNER_EXTENSOR(double) \
        FULL_MACRO_INNER_EXTENSOR(float) \
        FULL_MACRO_INNER_EXTENSOR(_Bool) \
        FULL_MACRO_EXTEND(void*) \
        FULL_MACRO_EXTEND(const void*), \
        default: "<unregistered type>" \
        FULL_MACRO_EXTENDED_TYPENAMES \
    )

#define __full_macro_file_print(file, x) do { fprintf(file, get_type_specifier_of(x), x); } while (0)

#define __full_macro_print_no_newline(x) do { file_print(stdout, x); } while(0)

#define __full_macro_print(x) do { file_print(stdout, x); putchar('\n'); } while(0)

#define __full_macro_dump_value(x) \
    do { printf("%s `%s` => ", typename_of(x), #x); file_print(stdout, x); putchar('\n'); } while (0)

#define __full_macro_type_is(x,T) (_Generic((x), T : 1, default : 0))

/* Section 3: Outer Macros */

/**
 * Returns a string containing the type name of a given value.
 */
#define typename_of(x) __full_macro_typename_of(x)

/**
 * Returns an appropriate printf-like type specifier for a given value.
 */
#define get_type_specifier_of(x) __full_macro_get_type_specifier_of(x)

/**
 * Writes the value of a variable to a given FILE*, matching the variable's type specifier.
 */
#define file_print(file, x) __full_macro_file_print(file, x)

/**
 * Prints a value without appending a newline to the end of it.
 */
#define print_no_newline(x) __full_macro_print_no_newline(x)

/**
 * Prints a variable to standard output and appends a newline.
 */
#define print(x) __full_macro_print(x)

/**
 * Prints some information about a variable.
 */
#define dump_value(x) __full_macro_dump_value(x)

/**
 * Returns 1 if the type of the first argument is the second argument, otherwise 0.
 */
#define type_is(x,T) __full_macro_type_is(x,T)

#ifdef __GNUC__

#define FULL_MACRO_INFER_H

/* We could just do `#include "infer.h"` here, but i want FullMacro to be a standalone header. */

#define let __auto_type

#endif



#endif
