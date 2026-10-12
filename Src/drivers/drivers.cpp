#include "./drivers.h"
#include "./tests.h"
#include "../hw/registers.h"
#include "../domain/types.h"
#include <cstdlib>

void enableClock(Port port)
{
    switch (port)
    {
    case Port::a:
        *rccIopenr |= static_cast<Register>(RCC_IOPENR_GPIOA_EN);
        return;
    case Port::c:
        *rccIopenr |= static_cast<Register>(RCC_IOPENR_GPIOC_EN);
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
