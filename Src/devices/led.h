#ifndef DEVICES_LED_H_
#define DEVICES_LED_H_

#include "./_helpers.h"
#include "../drivers/drivers.h"
#include "../domain/types.h"
#include <cstdint>

class Led
{
public:
    Led(Port port, Pin pin, Polarity polarity) :
            m_pin { port, pin, !DeviceHelpers::activeLevel(polarity) },
            m_polarity { polarity }
    {
    }

    Led(Port port, Pin pin) :
            Led { port, pin, Polarity::activeHigh }
    {
    }

    void on() const
    {
        m_pin.write(DeviceHelpers::activeLevel(m_polarity));
    }

    void off() const
    {
        m_pin.write(!DeviceHelpers::activeLevel(m_polarity));
    }

    void toggle() const
    {
        m_pin.write(!m_pin.isSet());
    }

    [[nodiscard]] bool isOn() const
    {
        return m_pin.isSet() == DeviceHelpers::activeLevel(m_polarity);
    }

private:
    OutputPin m_pin;
    Polarity m_polarity;
};

#endif
