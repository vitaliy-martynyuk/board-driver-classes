#ifndef DEVICES_LED_H_
#define DEVICES_LED_H_

#include "../drivers/drivers.h"
#include "../domain/types.h"
#include <cstdint>

enum class Polarity : std::uint8_t
{
    activeLow = 0, activeHigh = 1
};

class Led
{
public:
    Led(Port port, Pin pin, Polarity polarity) :
            m_pin { port, pin, !static_cast<bool>(polarity) },
            m_polarity { polarity }
    {
    }

    Led(Port port, Pin pin) :
            Led { port, pin, Polarity::activeHigh }
    {
    }

    void on() const
    {
        m_polarity == Polarity::activeHigh ? m_pin.set() : m_pin.reset();
    }

    void off() const
    {
        m_polarity == Polarity::activeHigh ? m_pin.reset() : m_pin.set();
    }

    void toggle() const
    {
        m_pin.write(!m_pin.isSet());
    }

    [[nodiscard]] bool isOn() const
    {
        return m_polarity == Polarity::activeHigh ?
                m_pin.isSet() : !m_pin.isSet();
    }

private:
    OutputPin m_pin;
    Polarity m_polarity;
};

#endif
