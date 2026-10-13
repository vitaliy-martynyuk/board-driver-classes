#ifndef DRIVERS_HELPERS_H_
#define DRIVERS_HELPERS_H_

#include "./_pin_mask.h"
#include "../hw/registers.h"
#include "../domain/constants.h"

namespace Helpers
{
    inline void writeField(volatile Register& reg, const PinMask& pinMask,
                           FieldWidth width, Register value)
    {
        const auto mask { pinMask.fieldMask(width) };
        const auto fieldValue { pinMask.fieldValue(value, width) };
        reg = (reg & ~mask) | fieldValue;
    }

    inline void writeBsrr(volatile Register& reg, const PinMask& pinMask,
                          bool level)
    {
        auto pos {
                level ? pinMask.pin() : pinMask.pin() + Constants::pinsPerPort };

        reg = 0x1u << pos;
    }

    inline bool isSet(Register reg, Register mask)
    {
        return (reg & mask) != 0u;
    }
}

#endif
