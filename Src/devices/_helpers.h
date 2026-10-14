#ifndef DEVICES_HELPERS_H_
#define DEVICES_HELPERS_H_

#include "../drivers/drivers.h"

enum class Polarity : std::uint8_t
{
    activeLow, activeHigh
};

namespace DeviceHelpers
{
    [[nodiscard]] constexpr bool activeLevel(Polarity polarity)
    {
        return polarity == Polarity::activeHigh;
    }
}

#endif
