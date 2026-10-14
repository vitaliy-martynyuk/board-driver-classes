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
            m_pin { port, pin, static_cast<bool>(polarity) },
            m_polarity { polarity }
    {
    }

    Led(Port port, Pin pin) :
            Led { port, pin, Polarity::activeHigh }
    {
    }

    void on() const
    {
        m_pin.set();
    }

    void off() const
    {
        m_pin.reset();
    }

    void toggle() const
    {
        if (m_pin.isSet())
        {
            m_pin.reset();
        }
        else
        {
            m_pin.set();
        }
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
