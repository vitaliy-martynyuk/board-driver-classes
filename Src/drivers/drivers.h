#ifndef DRIVERS_DRIVERS_H_
#define DRIVERS_DRIVERS_H_

#include "./_pin_mask.h"
#include "../hw/registers.h"

enum class Port
{
    a, c
};

volatile GpioRegisters* portRegisters(Port port);

void enableClock(Port port);

#endif
