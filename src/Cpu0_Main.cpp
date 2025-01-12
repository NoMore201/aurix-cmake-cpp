
#include "gpio.hpp"
#include "scu.hpp"

namespace
{

constexpr Hal::Gpio::Pin led{
    .port     = 0,
    .number   = 5,
    .function = Hal::Gpio::Function::Output,
    .speed    = Hal::Gpio::Speed::cmosAutomotiveSpeed1,
    .mode     = Hal::Gpio::Mode::outputPushPullGeneral,
};

} // anonymous namespace

extern "C"
{

// required by Ifx_Ssw_doCppInit
void _init(void)
{
}

void core0_main(void)
{
    Hal::Scu::disable_cpu_watchdog(Hal::Scu::get_cpu_password());

    Hal::Gpio::configure(led);

    while (true)
    {
    }
}
}
