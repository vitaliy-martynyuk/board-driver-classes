#ifndef DEVICES_LED_H_
#define DEVICES_LED_H_

#include "../drivers/drivers.h"
#include "../domain/types.h"
#include "./_helpers.h"
#include <cstdint>

class Led
{
public:
    Led(Port port, Pin pin, Polarity polarity) :
            m_pin { port, pin, !Helpers::activeLevel(polarity) },
            m_polarity { polarity }
    {
    }

    Led(Port port, Pin pin) :
            Led { port, pin, Polarity::activeHigh }
    {
    }

    void on() const
    {
        m_pin.write(Helpers::activeLevel(m_polarity));
    }

    void off() const
    {
        m_pin.write(!Helpers::activeLevel(m_polarity));
    }

    void toggle() const
    {
        m_pin.write(!m_pin.isSet());
    }

    [[nodiscard]] bool isOn() const
    {
        return m_pin.isSet() == Helpers::activeLevel(m_polarity);
    }

private:
    OutputPin m_pin;
    Polarity m_polarity;
};

#endif
