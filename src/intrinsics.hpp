#pragma once

#include "types.hpp"

namespace Ifx {

inline void ldmst(volatile auto* address, u32 mask, u32 value)
{
    __asm__ volatile("mov %H2,%1 \n    ldmst [%0]0,%A2" ::"a"(address), "d"(mask), "d"((long long)value));
}

inline void debug()
{
    __asm__ volatile ("debug" : : : "memory");
}

} // namespace Ifx