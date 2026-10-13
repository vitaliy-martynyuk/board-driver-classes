#ifndef HW_REGISTERS_H_
#define HW_REGISTERS_H_

#include "../domain/types.h"
#include <cstdint>

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
constexpr Register rccIopenrGpioaEn { 0x1u << 0 };
constexpr Register rccIopenrGpiocEn { 0x1u << 2 };

enum class MODER : std::uint8_t
{
    input = 0x0, output = 0x1, alternate = 0x2, analog = 0x3,
};

enum class OTYPER : std::uint8_t
{
    pushPull = 0x0, openDrain = 0x1,
};

enum class OSPEEDR : std::uint8_t
{
    veryLow = 0x0, low = 0x1, high = 0x2, veryHigh = 0x3,
};

enum class PUPDR : std::uint8_t
{
    none = 0x0, pullUp = 0x1, pullDown = 0x2,
};

enum class LCKR : std::uint8_t
{
    unlock = 0x0, lock = 0x1,
};

#endif
