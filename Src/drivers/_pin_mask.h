#ifndef DRIVERS_PIN_MASK_H_
#define DRIVERS_PIN_MASK_H_

#include "../domain/types.h"
#include "../domain/constants.h"
#include <cassert>
#include <cstdlib>
#include <cstdint>

enum class FieldWidth : std::uint8_t
{
    oneBit = 1, twoBits = 2
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

    [[nodiscard]] constexpr Register fieldMask(FieldWidth w) const
    {
        auto pos { shift(w) };

        switch (w)
        {
        case FieldWidth::oneBit:
            return static_cast<Register>(0x1u << pos);
        case FieldWidth::twoBits:
            return static_cast<Register>(0x3u << pos);
        default:
            assert(false && "Invalid pin width!");
            std::abort();
        }
    }

    [[nodiscard]] constexpr Register fieldValue(Register value,
                                                FieldWidth w) const
    {
        auto mask { fieldMask(w) };
        auto pos { shift(w) };

        switch (w)
        {
        case FieldWidth::oneBit:
        case FieldWidth::twoBits:
            return (value << pos) & mask;
        default:
            assert(false && "Invalid pin width!");
            std::abort();
        }
    }

private:
    Pin m_pin { Constants::minPin };

    constexpr Pin shift(FieldWidth w) const
    {
        return m_pin * static_cast<Pin>(w);
    }
};

#endif
