#include "timer.hpp"

#include <IfxStm_reg.h>

u64 Hal::Timer::now() {
    // TODO: disable interrupts
    u32 timerLsb = MODULE_STM0.TIM0SV.U;
    u32 timerMsb = MODULE_STM0.CAPSV.U;
    return static_cast<u64>(timerLsb) | (static_cast<u64>(timerMsb) << 32ULL);
}