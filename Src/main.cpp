#include "./drivers/drivers.h"
#include "./devices/led.h"

int main()
{
    Led ld4 { Port::a, 5 };         // active-high
    Led extLed { Port::c, 7 };                 // active-high
    InputPin b1 { Port::c, 13 };    // active-low

    while (true)
    {
        if (!b1.read())
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
