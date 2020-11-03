
#include "fullmacro/fullmacro.h"

struct Alpha {};
struct Beta {};

#undef FULL_MACRO_EXTENDED_TYPENAMES
#define FULL_MACRO_EXTENDED_TYPENAMES \
    FULL_MACRO_COMPLETE_EXTEND(struct Alpha) \
    FULL_MACRO_COMPLETE_EXTEND(struct Beta)


int main()
{
    let x = 10;
    let y = x * 1.5f;

    print(x);
    dump_value(x);

    //

    print(type_is(y, float));

    let name = typename_of(y);

    dump_value(name);

    //

    print_no_newline(x);

    print_no_newline(" + ");

    print_no_newline(y);

    print_no_newline(" = ");

    print(x + y);

    //

    struct Alpha alpha;

    print(typename_of(alpha));
    print(typename_of(&alpha));

    const struct Beta beta;

    print(typename_of(beta));
    print(typename_of(&beta));

}
