#ifndef DOMAIN_CONSTANTS_H_
#define DOMAIN_CONSTANTS_H_

#include "./types.h"

namespace Constants
{
    constexpr Pin minPin { 0 };
    constexpr Pin maxPin { 15 };
    constexpr Pin pinPerPort { maxPin + 1u };
}

#endif
