#ifndef DRIVERS_PORT_H_
#define DRIVERS_PORT_H_

#include "../hw/registers.h"
#include <cstdint>

enum class Port : std::uint8_t
{
    a, c
};

volatile GpioRegisters* portRegisters(Port);

void enableClock(Port);

#endif
