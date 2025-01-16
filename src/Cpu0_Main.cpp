
#include "gpio.hpp"
#include "intrinsics.hpp"
#include "scu.hpp"
#include "timer.hpp"

#include <array>

namespace
{

constexpr std::array<Hal::Gpio::Pin, 2> led_list{
    Hal::Gpio::Pin{
        .port     = 33,
        .number   = 4,
        .function = Hal::Gpio::Function::Output,
        .speed    = Hal::Gpio::Speed::cmosAutomotiveSpeed1,
        .mode     = Hal::Gpio::Mode::outputPushPullGeneral,
    },
    Hal::Gpio::Pin{
        .port     = 33,
        .number   = 5,
        .function = Hal::Gpio::Function::Output,
        .speed    = Hal::Gpio::Speed::cmosAutomotiveSpeed1,
        .mode     = Hal::Gpio::Mode::outputPushPullGeneral,
    },
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
    using Clock = Hal::Timer::Clock;
    Hal::Scu::disable_cpu_watchdog(Hal::Scu::get_cpu_password());
    Hal::Scu::disable_safety_watchdog(Hal::Scu::get_safety_password());

    Hal::Gpio::configure(led_list);

    const auto start_time = Clock::now();

    while (true)
    {
        const auto current_time = Clock::now();

        if (current_time - start_time > std::chrono::milliseconds(900)) {
            Ifx::debug();
        }
    }
}
}
