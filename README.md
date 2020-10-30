

# FullMacro

*Heretic C and nothing else*


---

FullMacro is a small header only library that provides powerful but heretic macros for the C language.

Its usage is _not_ intended for C++.

## Installation

The library has a couple header files that provide different macros, but no files depend on each other.
You can pick whichever you want and add it to your project.

*Note: If you're using CMake, it might not be able to tell the library's language, if such is the case,
you will need to add `fullmacro.c` even though no linking has to be performed.* 

## Contents

- `fulmacro.h` - The library's protagonist. Provides multiple type sensitive macros, and to do such, requires C11.

- `infer.h` - Provides macros to help performing type inference (requires GNUC).

- `version.h` - Auxiliary macros to help determining the C standard of the environment.

- `common_bool.h` - Long story short, `<stdbool.h>` but compatible with C89 and C94.

- `shut_up.h` - Silences the file output of most functions defined in `<stdio.h>`.

## `fullmacro.h`

This is the first and main file of this library, it requires C11 to work properly.
 
The most basic operation provided by `fullmacro.h` is printing.
The provided macros will find the suitable type format for their arguments.
 
The most basic macro used to print values, is `print`, which will take a single argument and display its value to 
`stdout`, appending a newline to it.

```c
#include <fullmacro/fullmacro.h>

int main()
{
    print(10);     // Writes 10
    print("beep"); // Writes beep
    print(-4.3f);  // Writes -4.3

    return 0;    
}
```

If one wants to find the type specifier of a given value for other purposes, it can also use `get_type_specifier_of`.

```c

long double x = 1;

char *specifier = get_type_specifier_of(x);

fprintf(stderr, specifier, x);

```

Note that there is a macro to write data to files other than `stdout`, `file_print` which output is identical
to the one of `print`, except no newline is added.
If one wants to write a value to `stdout` without appending a newline to the output, they can use also use
the `print_no_newline` macro.

FullMacro also provides macros to retrieve the type of a value.
The `typename_of` macro returns a string containing the name of a builtin type, although non builtin names can be
implemented as shown later.
This macro can in fact be used to check the the type of a given value, but a better alternative is available.
The `type_is` macro compares its first argument to the type provided as the second argument,
and returns 1 or 0 if the types match.

```c
int x = 10;

print(typename_of(x)); // int

print(type_is(x, int)); // 1
print(type_is(x, float)); // 0
print(type_is(x, double)); // 0
print(type_is(&x, int*)); // 1
```
 
Note that `typename_of` discards the const qualifier of the given value, and `type_is` comparisons against any constant
type will always fail (but this rule does not apply to pointers to constant types).
 
```c
const int x = 10;

char *name = typename_of(x);

print(name); // Prints "int"

print(type_is(x, int));       // 1
print(type_is(x, double));    // 0
print(type_is(x, const int)); // 0 (comparison against const will always fail)

print(typename_of(&x)); // Prints "const int *"

print(type_is(&x, int*));       // 0
print(type_is(&x, const int*)); // 1

```

`fullmacro.h` will also perform all declarations of `infer.h` if it detects that GNUC is present in the current
 environment (`fullmacro.h` does not require the presence of `infer.h` to work properly though). 

## `infer.h`

This header file requires GNUC to work, but C11 is not a requirement.
A single symbol is declared, `let`, which can substitute the type of a variable definition, if such variable is
assigned at its declaration. To perform type inference on a constant, `const let` is available.
 
```c

let x = 10;
let s = "beep";

print(x); // 10
print(s); // beep

print(typename_of(x)); // int
print(typename_of(s)); // char *

const let y = x + 1.5f;

print(typename_of(y)); // float

```

## `version.h`

This header file declares multiple macros to help determining the standard of the current execution.

The `__HAS_C??` family of macros expand to the integer constant 1 if their respective standard is available, or 0 if it
is not.

- `__HAS_C89`: 1 if the C89 standard is present, otherwise 0.
- `__HAS_C94`: 1 if the C94 standard is present, otherwise 0.
- `__HAS_C99`: 1 if the C99 standard is present, otherwise 0.
- `__HAS_C11`: 1 if the C11 standard is present, otherwise 0.
- `__HAS_C18`: 1 if the C18 standard is present, otherwise 0.

The `__C??_VERSION_VALUE` family of macros expand to long constants that represent the version value of C standards.

- `__C99_VERSION_VALUE`: The long constant that represents the value defined in C99.
- `__C11_VERSION_VALUE`: The long constant that represents the value defined in C11.
- `__C18_VERSION_VALUE`: The long constant that represents the value defined in C18.


## `common_bool.h`

This macro will have the same effects described at the man page of `stdbool.h`, except it will not malfunction with C89
or C94.

## `shut_up.h`

Including this file will define macros that silence any call to the following functions from `stdio.h`:
`printf`, `fprintf`, `dprintf`, `vprintf`, `vfprintf`, `vdprintf`, `fputc`, `fputs`, `putc`, `putchar` and `puts`.


###  Extending `typename_of`

At the current moment, the `print` family of macros only accepts builtin C types, (not pointer to them) `char *`, and
`void *`. An attempt to `print` any other type will error.

A similar rule applies to `typename_of`, but it will return a string representing an unregistered type
 (probably `"<unregistered type>"`).
 
 It is possible to register custom types to `typename_of`, by using the extension macros.
 The `FULL_MACRO_EXTENDED_TYPENAMES` macro can be undefined and then redefined to something else by the user, if
that is the case, then the contents of such macro can be defined to zero or more calls to the following extension
macros:

- `FULL_MACRO_EXTEND(type)`: Registers the single given parameter type into `typename_of`.

- `FULL_MACRO_COMPLETE_EXTEND(type)`: Registers the parameter type, the pointer to given type, and the const pointer to
 the type into `typename_of`.

```c

#include "fullmacro/fullmacro.h"

struct Alpha {};
struct Beta {};
struct Gamma {};

#undef FULL_MACRO_EXTENDED_TYPENAMES
#define FULL_MACRO_EXTENDED_TYPENAMES \
    FULL_MACRO_COMPLETE_EXTEND(struct Alpha) \
    FULL_MACRO_COMPLETE_EXTEND(struct Beta) \
    FULL_MACRO_EXTEND(struct Gamma)
    

int main()
{
    const struct Alpha alpha;
    struct Beta beta;
    struct Gamma gamma;

    print(typename_of(alpha)); // struct Alpha
    print(typename_of(beta)); // struct beta
    print(typename_of(gamma)); // struct Gamma

    print(typename_of(&alpha)); // const struct Alpha *
    print(typename_of(&beta)); // struct Beta *
    print(typename_of(&gamma)); // <unregistered type>

    // struct Gamma* is not registered because we have only used `FULL_MACRO_EXTEND` on it.
    // Only FULL_MACRO_COMPLETE_EXTENDS registers the pointers to a given type.
}
```
