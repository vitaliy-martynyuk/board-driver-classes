#ifndef DRIVERS_INPUT_PIN_H_
#define DRIVERS_INPUT_PIN_H_

#include "./_pin_mask.h"
#include "./_port.h"
#include "./_helpers.h"
#include "../domain/types.h"
#include "../hw/registers.h"

class InputPin
{
public:
    InputPin(const InputPin&) = delete;

    InputPin(Port port, Pin pin, Gpio::Pull pullValue = Gpio::Pull::none) :
            m_reg { portRegisters(port) }, m_pinMask { pin }
    {
        using namespace Gpio;

        enableClock(port);

        const auto pull { static_cast<Register>(pullValue) };
        const auto mode { static_cast<Register>(Mode::input) };

        Helpers::writeField(m_reg->pupdr, m_pinMask, FieldWidth::twoBits, pull);
        Helpers::writeField(m_reg->moder, m_pinMask, FieldWidth::twoBits, mode);
    }

    [[nodiscard]] bool read() const
    {
        const auto mask { m_pinMask.fieldMask(FieldWidth::oneBit) };

        return Helpers::isSet(m_reg->idr, mask);
    }

private:
    volatile GpioRegisters* const m_reg { };
    PinMask m_pinMask;
};

#endif
