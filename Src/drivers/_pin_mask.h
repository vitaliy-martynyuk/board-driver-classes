#ifndef DRIVERS_PIN_MASK_H_
#define DRIVERS_PIN_MASK_H_

#include "../domain/types.h"
#include "../domain/constants.h"
#include <cassert>
#include <cstdlib>

enum class PW
{
    s,  // 1 bit
    d,  // 2 bits
};

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

    [[nodiscard]] constexpr Register fieldMask(PW w) const
    {
        switch (w)
        {
        case PW::s:
            return static_cast<Register>(0x1u << m_pin);
        case PW::d:
            return static_cast<Register>(0x3u << static_cast<Pin>(m_pin * 2));
        default:
            assert(false && "Invalid pin width!");
            std::abort();
        }
    }

    [[nodiscard]] constexpr Register fieldValue(Register value, PW w) const
    {
        auto mask { fieldMask(w) };

        switch (w)
        {
        case PW::s:
            return (value << m_pin) & mask;
        case PW::d:
            return (value << static_cast<Pin>(m_pin * 2)) & mask;
        default:
            assert(false && "Invalid pin width!");
            std::abort();
        }
    }

private:
    Pin m_pin { Constants::minPin };
};

#endif
