#include "./drivers/drivers.h"
#include <cstdint>

int main(void)
{
    OutputPin ld4 { Port::a, 5 };
    ld4.set();
    for (;;);
}
