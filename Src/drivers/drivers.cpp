#include "./drivers.h"
#include "./_port.h"
#include "./_pin_mask.h"
#include "./_tests.h"
#include "../hw/registers.h"
#include "../domain/types.h"
#include <cstdlib>
#include <cassert>

void enableClock(Port port)
{
    switch (port)
    {
    case Port::a:
        *rccIopenr |= rccIopenrGpioaEn;
        return;
    case Port::c:
        *rccIopenr |= rccIopenrGpiocEn;
        return;
    default:
        assert(false && "Unsupported port!");
        std::abort();
    }
}

volatile GpioRegisters* portRegisters(Port port)
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
    }
}

namespace Helpers
{
    void lockPort(volatile GpioRegisters* const port)
    {
        port->lckr |= (static_cast<Register>(0x1 << 16));
        port->lckr |= (static_cast<Register>(0x0 << 16));
        port->lckr |= (static_cast<Register>(0x1 << 16));
    }

    void setPinLock(volatile GpioRegisters* const port, Pin pin, LCKR lock)
    {
        const auto value { static_cast<Register>(lock) };
        port->lckr |= (PinMask { pin }.fieldValue(value, FieldWidth::oneBit));
    }
}
