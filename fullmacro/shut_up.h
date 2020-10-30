
#ifndef  __SHUT_UP
#define  __SHUT_UP

/* Yeah, I know, I could have just done #define printf(...) and the job would be done */
/* But I want to keep C89 support. */

#include <stdio.h>
#include <stdarg.h>


static int shut_up_puts(const char *s);

static int shut_up_printf(const char* str, ...)
{(void)str;  (void) shut_up_puts; return 0;}

static int shut_up_fprintf(FILE* file, const char* str, ...)
{(void)file;  (void) str; (void) shut_up_printf; return 0;}

static int shut_up_dprintf(int i, const char* f, ...)
{(void)i;  (void)f; (void) shut_up_fprintf; return 0;}

static int shut_up_vprintf(const char *format, va_list ap)
{(void)format;  (void)ap; (void) shut_up_dprintf; return 0;}

static int shut_up_vfprintf(FILE *stream, const char *format, va_list ap)
{(void)stream;  (void)format; (void)ap; (void) shut_up_vprintf; return 0;}

static int shut_up_vdprintf(int fd, const char *format, va_list ap)
{(void) fd; (void) format; (void) ap; (void) shut_up_vfprintf; return 0;}

static int shut_up_fputc(int c, FILE *stream)
{(void)c;  (void) stream; return 0; }

static int shut_up_fputs(const char *s, FILE *stream)
{(void)s;  (void) stream; (void) shut_up_fputc; return 0;}

static int shut_up_putc(int c, FILE *stream)
{(void)c; (void) stream; (void) shut_up_fputs; return 0;}

static int shut_up_putchar(int c)
{(void)c;  (void) shut_up_putc; return 0;}

static int shut_up_puts(const char *s)
{(void)s;  (void) shut_up_putchar; return 0;}

#define printf shut_up_printf
#define fprintf shut_up_fprintf
#define dprintf shut_up_dprintf
#define vprintf shut_up_vprintf
#define vfprintf shut_up_vfprintf
#define vdprintf shut_up_vdprintf
#define fputc shut_up_fputc
#define fputs shut_up_fputs
#define putc shut_up_putc
#define putchar shut_up_putchar
#define puts shut_up_puts



#endif