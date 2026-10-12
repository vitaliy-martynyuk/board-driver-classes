#ifndef DRIVERS__PIN_MASK_H_
#define DRIVERS__PIN_MASK_H_

#include "../domain/types.h"
#include "../domain/constants.h"
#include <cassert>

class PinMask
{
public:
    constexpr explicit PinMask(Pin pin) :
            m_pin { pin }
    {
        assert(m_pin <= Constants::maxPin);
    }

    [[nodiscard]] constexpr Pin pin() const
    {
        return m_pin;
    }

    [[nodiscard]] constexpr Register fieldMask() const
    {
        return static_cast<Register>(0x1u << m_pin);
    }

    [[nodiscard]] constexpr Register field2Mask() const
    {
        return static_cast<Register>(0x3u << static_cast<Pin>(m_pin * 2));
    }

private:
    Pin m_pin { Constants::minPin };
};

#endif
