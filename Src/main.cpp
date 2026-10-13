#include "./drivers/drivers.h"
#include <cstdint>

static void delay()
{
    volatile std::uint32_t i = 0;
    while (i < 180000)
    {
        ++i;
    }
}

int main(void)
{
    OutputPin ld4 { Port::a, 5 };
    while (true)
    {
        ld4.write(!ld4.isSet());
        delay();
    }
}
