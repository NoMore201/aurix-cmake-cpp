#include "gpio.hpp"
#include "error.hpp"
#include "intrinsics.hpp"
#include "scu.hpp"

#include <IfxPort_reg.h>

namespace
{

Ifx_P& get_port(u8 port)
{
    switch (port)
    {
        case 0:
            return MODULE_P00;
        case 2:
            return MODULE_P02;
        case 10:
            return MODULE_P10;
        case 11:
            return MODULE_P11;
        case 13:
            return MODULE_P13;
        case 14:
            return MODULE_P14;
        case 20:
            return MODULE_P20;
        case 21:
            return MODULE_P21;
        case 22:
            return MODULE_P22;
        case 23:
            return MODULE_P23;
        case 32:
            return MODULE_P32;
        case 33:
            return MODULE_P33;
        case 34:
            return MODULE_P34;
        default:
            VERIFY_NOT_REACHED();
    }
}

} // anonymous namespace

void Hal::Gpio::configure(const Pin& pin)
{
    auto& port = get_port(pin.port);

    const auto pdr_index  = pin.number / 8U;
    const auto pdr_shift  = (pin.number % 8U) * 4U;
    const auto iocr_index = pin.number / 4U;
    const auto iocr_shift = (pin.number % 4) * 8U;

    Scu::CpuEndinitGuard guard{Scu::get_cpu_password()};

    // write pad driver
    volatile auto* pdr_list = &port.PDR0.U;
    Ifx::ldmst(&(pdr_list[pdr_index]), (0xFUL << pdr_shift), (pin.speed << pdr_shift));

    // write pin mode
    volatile auto* iocr_list = &port.IOCR0.U;
    Ifx::ldmst(&(iocr_list[iocr_index]), (0xFFUL << iocr_shift), (pin.mode << iocr_shift));
}
