#ifndef DRIVERS_OUTPUT_PIN_H_
#define DRIVERS_OUTPUT_PIN_H_

#include "./_port.h"
#include "./_pin_mask.h"
#include "../domain/types.h"
#include "../domain/constants.h"
#include <cassert>

class OutputPin
{
public:
    OutputPin(const OutputPin&) = delete;

    OutputPin(Port port, Pin pin) :
            m_port { port }, m_reg { portRegisters(port) }, m_pinMask { pin }
    {
        using namespace Gpio;

        enableClock(m_port);

        const auto type { static_cast<Register>(Type::pushPull) };
        const auto speed { static_cast<Register>(Speed::low) };
        const auto pull { static_cast<Register>(Pull::none) };
        const auto mode { static_cast<Register>(Mode::output) };

        writeField(m_reg->otyper, FieldWidth::oneBit, type);
        writeField(m_reg->ospeedr, FieldWidth::twoBits, speed);
        writeField(m_reg->pupdr, FieldWidth::twoBits, pull);
        writeField(m_reg->moder, FieldWidth::twoBits, mode);
    }

    void set() const
    {
        writeField(m_reg->bsrr, FieldWidth::oneBit, 0x1);
    }

    void reset() const
    {
        writeField(m_reg->bsrr, FieldWidth::oneBit, 0x0);
    }

    void write(bool level) const
    {
        writeField(m_reg->bsrr, FieldWidth::oneBit,
                   static_cast<Register>(level));
    }

    [[nodiscard]] bool isSet() const
    {
        return static_cast<bool>(m_reg->bsrr
                & m_pinMask.fieldMask(FieldWidth::oneBit));
    }

private:
    Port m_port { };
    volatile GpioRegisters* const m_reg { };
    PinMask m_pinMask;

    void writeField(volatile Register& reg, FieldWidth width,
                    Register value) const
    {
        const auto mask { m_pinMask.fieldMask(width) };
        const auto fieldValue { m_pinMask.fieldValue(value, width) };
        reg = (reg & ~mask) | fieldValue;
    }
};

#endif
