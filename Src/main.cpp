#include "./drivers/drivers.h"
#include "./devices/led.h"
#include "./devices/button.h"

int main()
{
    Led ld4 { Port::a, 5 };         // active-high
    Led extLed { Port::c, 7 };      // active-high
    Button b1 { Port::c, 13 };      // active-low

    while (true)
    {
        b1.sample();
        if (b1.isPressed())
        {
            ld4.on();
            extLed.off();
        }
        else
        {
            ld4.off();
            extLed.on();
        }
    }
}
