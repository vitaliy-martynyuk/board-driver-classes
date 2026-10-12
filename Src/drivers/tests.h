#ifndef DRIVERS_TESTS_H_
#define DRIVERS_TESTS_H_

#include "./_pin_mask.h"
#include "../domain/constants.h"

using namespace Constants;

constexpr PinMask pin0 { minPin };
constexpr PinMask pin15 { maxPin };

static_assert(pin0.pin() == 0);
static_assert(pin0.fieldMask() == 0x1);
static_assert(pin0.field2Mask() == 0x3);
static_assert(pin15.pin() == 15);
static_assert(pin15.fieldMask() == (0x1u << 15));
static_assert(pin15.field2Mask() == (0x3u << 30));

#endif
