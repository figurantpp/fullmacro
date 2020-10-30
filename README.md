

# FullMacro

*Heretic C and nothing more*


---

FullMacro is a small header only library that provides powerful but heretic macros for the C language.

Its usage is _not_ intended for C++.

## Instalation

The library has a couple header files that provide different macros, but no files depend on each other.
You can pick whichever you want and add it to your project.

*Note: If you're using CMake, it might not be able to tell the library's language, if such is the case,
you will need to include `fullmacro.c` even though no linking has to be performed.* 

## Contents

- `fulmacro.h` - The library's protagonist. Provides multiple type sensitive macros, and to do such, requires C11.

- `infer.h` - Provides macros to help performing type inference (requires GNUC).

- `version.h` - Auxiliary macros to help determining the C standard of the environment.

- `common_bool.h` - Long story short, `<stdbool.h>` but compatible with C89.

- `shut_up.h` - Silences the file output of most functions defined in `<stdio.h>`.

## `fullmacro.h`

This is the first and main file of this library, it requires C11 to work properly.
 
The most basic operation provided by `fullmacro.h` is printing.
The provided macros will find the suitable type format for their arguments.
 
The most basic macro used to print values, is `print`, which will take a single argument and display its value to 
`stdout`, appending a newline to the end of it.

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
If one wants to write a value to `stdout` without pushing a newline to the end of the output, they can use also use
the `print_no_newline` macro.

FullMacro also provides macros to retrieve the type of a value.
The `typename_of` macro returns a string containing the name of a builtin type, although non builtin names can be
implemented as shown later.
This macro can indeed be used to
check the the type of a given value, but a better alternative is available.
The `type_is` macro compares its first argument to the type provided in the second argument,
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

print(type_is(x, int)); // 1
print(type_is(x, double)); // 0
print(type_is(x, const int)); // 0 (comparison against const will always fail)

print(typename_of(&x)); // Prints "const int"

print(type_is(&x, int*)); // 0
print(type_is(&x, const int*)); // 1

```

`fullmacro.h` will also perform all declarations of `infer.h` if it detects that GNUC is present in the current
 environment (`fullmacro.h` does not require `infer.h` to be work properly though). 

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
