#pragma once

#include "types.hpp"

namespace Hal::Scu {

using Password = u16;

void clear_cpu_endinit(Password);
void set_cpu_endinit(Password);
void disable_cpu_watchdog(Password);
Password get_cpu_password();

void clear_safety_endinit(Password);
void set_safety_endinit(Password);
void disable_safety_watchdog(Password);
Password get_safety_password();

struct CpuEndinitGuard {

    Password password;

    explicit CpuEndinitGuard(Password pwd)
        : password(pwd)
    {
        clear_cpu_endinit(password);
    }

    ~CpuEndinitGuard() {
        set_cpu_endinit(password);
    }

};

struct SafetyEndinitGuard {

    Password password;

    explicit SafetyEndinitGuard(Password pwd)
        : password(pwd)
    {
        clear_safety_endinit(password);
    }

    ~SafetyEndinitGuard() {
        set_safety_endinit(password);
    }

};


} // namespace Hal::Scu