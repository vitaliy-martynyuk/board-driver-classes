#ifndef DEVICES_LED_H_
#define DEVICES_LED_H_

#include "../drivers/drivers.h"
#include "../domain/types.h"
#include <cstdint>

enum class Polarity : std::uint8_t
{
    activeLow, activeHigh
};

class Led
{
public:
    Led(Port port, Pin pin, Polarity polarity) :
            m_pin { port, pin, !activeLevel(polarity) }, m_polarity { polarity }
    {
    }

    Led(Port port, Pin pin) :
            Led { port, pin, Polarity::activeHigh }
    {
    }

    void on() const
    {
        m_pin.write(activeLevel(m_polarity));
    }

    void off() const
    {
        m_pin.write(!activeLevel(m_polarity));
    }

    void toggle() const
    {
        m_pin.write(!m_pin.isSet());
    }

    [[nodiscard]] bool isOn() const
    {
        return m_pin.isSet() == activeLevel(m_polarity);
    }

private:
    OutputPin m_pin;
    Polarity m_polarity;

    [[nodiscard]] static constexpr bool activeLevel(Polarity polarity)
    {
        return polarity == Polarity::activeHigh;
    }
};

#endif
