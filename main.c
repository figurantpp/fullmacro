
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
}
