#include "./drivers/drivers.h"
#include <cstdint>

//static void delay()
//{
//    volatile std::uint32_t i = 0;
//    while (i < 180000)
//    {
//        ++i;
//    }
//}

int main(void)
{
    OutputPin ld4 { Port::a, 5 };
    InputPin b1 { Port::c, 13 };

    while (true)
    {
        ld4.write(!b1.read());
    }
}
