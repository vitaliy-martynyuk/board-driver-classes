#ifndef HW_REGISTERS_H_
#define HW_REGISTERS_H_

#include "../domain/types.h"

#define RCC_IOPENR_GPIOA_EN (0x1u)
#define RCC_IOPENR_GPIOC_EN (0x1u << 2)

struct GpioRegisters
{
    volatile Register moder;       // 0x00
    volatile Register otyper;      // 0x04
    volatile Register ospeedr;     // 0x08
    volatile Register pupdr;       // 0x0C
    volatile Register idr;         // 0x10
    volatile Register odr;         // 0x14
    volatile Register bsrr;        // 0x18
    volatile Register lckr;        // 0x1C
    volatile Register afrl;        // 0x20
    volatile Register afrh;        // 0x24
    volatile Register brr;         // 0x28
};
static_assert(sizeof(GpioRegisters) == 0x2C);

inline volatile GpioRegisters* const gpioA { reinterpret_cast<GpioRegisters*>(0x5000'0000u) };
inline volatile GpioRegisters* const gpioC { reinterpret_cast<GpioRegisters*>(0x5000'0800u) };
inline volatile Register* const rccIopenr { reinterpret_cast<volatile Register*>(0x4002'1034u) };

#endif
