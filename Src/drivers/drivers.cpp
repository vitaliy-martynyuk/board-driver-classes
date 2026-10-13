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
        break;
    case Port::c:
        *rccIopenr |= rccIopenrGpiocEn;
        break;
        return;
    default:
        assert(false && "Unsupported port!");
        std::abort();
    }

    *rccIopenr; // read RCC to make sure changes applied
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
