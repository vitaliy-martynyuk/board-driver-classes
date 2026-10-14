#ifndef DEVICES__HELPERS_H_
#define DEVICES__HELPERS_H_

#include "../drivers/drivers.h"

namespace Helpers
{
    [[nodiscard]] constexpr bool activeLevel(Polarity polarity)
    {
        return polarity == Polarity::activeHigh;
    }
}

#endif
