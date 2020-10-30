

#include "fullmacro/version.h"
#include "fullmacro/fullmacro.h"

#include <stdio.h>

int main()
{
    print(__HAS_C89);
    print(__HAS_C99);
    print(__HAS_C94);
    print(__HAS_C11);
    print(__HAS_C18);
}
