#ifndef DEVICES_BUTTON_H_
#define DEVICES_BUTTON_H_

#include "./_helpers.h"
#include "../drivers/drivers.h"
#include "../domain/types.h"
#include "../hw/registers.h"
#include <cstdint>
#include <optional>

enum class ButtonEvent : std::uint8_t
{
    pressed, released
};

class Button
{
public:
    Button(Port port, Pin pin, Gpio::Pull pull, Polarity polarity,
           std::uint8_t stableTicks) :
            m_pin { port, pin, pull }, m_event { ButtonEvent::released },
            m_polarity { polarity }, m_debounceCountMax { stableTicks }
    {
    }

    Button(Port port, Pin pin) :
            Button { port, pin, Gpio::Pull::none, Polarity::activeLow, 20u }
    {
    }

    void sample()
    {
        const bool newState { m_pin.read()
                == DeviceHelpers::activeLevel(m_polarity) };
        const bool currentState { isPressed() };
        if (newState != currentState)
        {
            if (m_debounceCount == (m_debounceCountMax - 1))
            {
                m_event =
                        currentState ?
                                ButtonEvent::released : ButtonEvent::pressed;
                m_debounceCount = 0;
                m_eventFlag = true;
            }
            else
            {
                ++m_debounceCount;
            }
        }
        else
        {
            m_debounceCount = 0;
        }
    }

    [[nodiscard]] std::optional<ButtonEvent> takeEvent()
    {
        std::optional<ButtonEvent> res { std::nullopt };
        if (m_eventFlag)
        {
            res = m_event;
        }

        m_eventFlag = false;
        return res;
    }

    [[nodiscard]] bool isPressed() const
    {
        return m_event == ButtonEvent::pressed;
    }

private:
    InputPin m_pin;
    ButtonEvent m_event;
    Polarity m_polarity;
    std::uint8_t m_debounceCount { 0 };
    std::uint8_t m_debounceCountMax { 0 };
    bool m_eventFlag { false };
};

#endif
