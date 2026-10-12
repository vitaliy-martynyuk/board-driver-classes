#ifndef DRIVERS_DRIVERS_H_
#define DRIVERS_DRIVERS_H_

#include "../hw/registers.h"
#include "../domain/types.h"
#include <cassert>
#include <cstdlib>

enum class Port
{
    a, c
};

constexpr volatile GpioRegisters* const portRegisters(Port port)
{
    switch (port)
    {
    case Port::a:
        return gpioA;
    case Port::c:
        return gpioC;
    default:
        assert(false && "Unsupported port!");
        std::abort();
    };
}

constexpr void enableClock(Port port)
{
    switch (port)
    {
    case Port::a:
        *rccIopenr |= static_cast<Register>(0x1u);
    case Port::c:
        *rccIopenr |= static_cast<Register>(0x1u << 2);
    default:
        assert(false && "Unsupported port!");
        std::abort();
    };
}

class PinMask
{
public:
    constexpr explicit PinMask(Pin pin) :
            m_pin { pin }
    {
        assert((m_pin >= 0) && (m_pin <= 15));
    }

    constexpr Pin pin() const
    {
        return m_pin;
    }

    constexpr Register bitMask() const
    {
        return static_cast<Register>(0x1u << m_pin);
    }

    constexpr Register bit2Mask() const
    {
        return static_cast<Register>(0x3u << static_cast<Pin>(m_pin * 2));
    }

private:
    Pin m_pin { 0 };
};

#endif
