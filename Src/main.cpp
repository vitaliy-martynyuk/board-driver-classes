#include "./drivers/drivers.h"

int main()
{
    OutputPin ld4 { Port::a, 5 };   // active-high
    InputPin b1 { Port::c, 13 };    // active-low

    while (true)
    {
        ld4.write(!b1.read());
    }
}
