#ifndef DRIVERS_TESTS_H_
#define DRIVERS_TESTS_H_

#include "./drivers.h"

constexpr PinMask pin0 { 0 };
constexpr PinMask pin15 { 15 };

static_assert(pin0.pin() == 0);
static_assert(pin0.bitMask() == 0x1);
static_assert(pin0.bit2Mask() == 0x3);
static_assert(pin15.pin() == 15);
static_assert(pin15.bitMask() == (0x1u << 15));
static_assert(pin15.bit2Mask() == (0x3u << 30));

#endif
