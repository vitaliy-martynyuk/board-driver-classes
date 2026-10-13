#ifndef DRIVERS_OUTPUT_PIN_H_
#define DRIVERS_OUTPUT_PIN_H_

#include "./_port.h"
#include "./_pin_mask.h"
#include "./_helpers.h"
#include "../domain/types.h"
#include "../domain/constants.h"
#include <cassert>

class OutputPin
{
public:
    OutputPin(const OutputPin&) = delete;

    OutputPin(Port port, Pin pin, bool level = false) :
            m_port { port }, m_reg { portRegisters(port) }, m_pinMask { pin }
    {
        using namespace Gpio;

        enableClock(m_port);

        const auto type { static_cast<Register>(Type::pushPull) };
        const auto speed { static_cast<Register>(Speed::low) };
        const auto pull { static_cast<Register>(Pull::none) };
        const auto mode { static_cast<Register>(Mode::output) };

        Helpers::writeField(m_reg->otyper, m_pinMask, FieldWidth::oneBit, type);
        Helpers::writeField(m_reg->ospeedr, m_pinMask, FieldWidth::twoBits,
                            speed);
        Helpers::writeField(m_reg->pupdr, m_pinMask, FieldWidth::twoBits, pull);
        Helpers::writeBsrr(m_reg->bsrr, m_pinMask, level);
        Helpers::writeField(m_reg->moder, m_pinMask, FieldWidth::twoBits, mode);
    }

    void set() const
    {
        Helpers::writeBsrr(m_reg->bsrr, m_pinMask, true);
    }

    void reset() const
    {
        Helpers::writeBsrr(m_reg->bsrr, m_pinMask, false);
    }

    void write(bool level) const
    {
        Helpers::writeBsrr(m_reg->bsrr, m_pinMask, level);
    }

    [[nodiscard]] bool isSet() const
    {
        const auto mask { m_pinMask.fieldMask(FieldWidth::oneBit) };

        return (m_reg->odr & mask) != 0u;
    }

private:
    Port m_port { };
    volatile GpioRegisters* const m_reg { };
    PinMask m_pinMask;
};

#endif
