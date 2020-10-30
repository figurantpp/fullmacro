
#ifndef __VERSIONS_H /* Include Guard */

#define C99_VERSION_VALUE 199901L
#define C11_VERSION_VALUE 201112L
#define C18_VERSION_VALUE 201710L

#if defined(__STDC__)  || defined(_MSC_VER)

#define __HAS_C89 1

/* If there is the __STDC_VERSION__ macro
    introduced in C94 */
#ifdef __STDC_VERSION__

#define __HAS_C94 1

/* If such macro has C99*/
#if __STDC_VERSION__ >= C99_VERSION_VALUE

#define __HAS_C99 1

#endif /* End C99 */

/* If such macro has C11 */
#if __STDC_VERSION__ >= C11_VERSION_VALUE

#define __HAS_C11 1

#endif /* End C11 */

/* If such macro includes C18 */
#if __STDC_VERSION__ >= C18_VERSION_VALUE

#define __HAS_C18 1

#endif /* End C18 */


#endif /* End __STDC_VERSION__ */

#endif /* End __STDC__ */


/* Defining Macros as 0 if they're not already defined */

#ifndef __HAS_C89
#define __HAS_C89 0
#endif

#ifndef __HAS_C94
#define __HAS_C94 0
#endif

#ifndef __HAS_C99
#define __HAS_C99 0
#endif

#ifndef __HAS_C11
#define __HAS_C11 0
#endif

#ifndef __HAS_C18
#define __HAS_C18 0
#endif


#endif /* End Include Guard */

