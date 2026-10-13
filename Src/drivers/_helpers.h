#ifndef DRIVERS__HELPERS_H_
#define DRIVERS__HELPERS_H_

#include "../hw/registers.h"
#include "../domain/types.h"

namespace Helpers
{
    void lockPort(volatile GpioRegisters* const);
    void setPinLock(volatile GpioRegisters* const, Pin, LCKR);
}

#endif
