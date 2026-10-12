#ifndef DRIVERS_TESTS_H_
#define DRIVERS_TESTS_H_

#include "./_pin_mask.h"
#include "../domain/constants.h"

constexpr PinMask pin0 { Constants::minPin };
constexpr PinMask pin15 { Constants::maxPin };

static_assert(pin0.pin() == 0);
static_assert(pin0.fieldMask(FieldWidth::oneBit) == 0x1);
static_assert(pin0.fieldMask(FieldWidth::twoBits) == 0x3);

static_assert(pin15.pin() == 15);
static_assert(pin15.fieldMask(FieldWidth::oneBit) == (0x1u << 15));
static_assert(pin15.fieldMask(FieldWidth::twoBits) == (0x3u << 30));

static_assert(pin0.fieldValue(0b1, FieldWidth::oneBit) == 0x1);
static_assert(pin0.fieldValue(0b10, FieldWidth::twoBits) == 0x2);

static_assert(pin15.fieldValue(0b1, FieldWidth::oneBit) == (0x1u << 15));
static_assert(pin15.fieldValue(0b11, FieldWidth::twoBits) == (0x3u << 30));

static_assert(pin0.fieldValue(0b11, FieldWidth::oneBit) == 0x1);
static_assert(pin0.fieldValue(0b111, FieldWidth::twoBits) == 0x3);

#endif
