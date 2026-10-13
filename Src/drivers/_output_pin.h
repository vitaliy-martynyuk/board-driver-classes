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

    constexpr OutputPin(Port port, Pin pin) :
            m_port { port }, m_pin { pin }
    {
        assert(m_pin <= Constants::maxPin);

        enableClock(m_port);
        auto* const reg { portRegisters(m_port) };
        const PinMask pinMask { pin };

        const auto type { static_cast<Register>(OTYPER::pushPull) };
        const auto speed { static_cast<Register>(OSPEEDR::low) };
        const auto pull { static_cast<Register>(PUPDR::none) };
        const auto mode { static_cast<Register>(MODER::output) };

        reg->otyper |= pinMask.fieldValue(type, FieldWidth::oneBit);
        reg->ospeedr |= pinMask.fieldValue(speed, FieldWidth::twoBits);
        reg->pupdr |= pinMask.fieldValue(pull, FieldWidth::twoBits);
        reg->moder |= pinMask.fieldValue(mode, FieldWidth::twoBits);
    }

private:
    Port m_port { Port::a };
    Pin m_pin { Constants::minPin };
};

#endif
