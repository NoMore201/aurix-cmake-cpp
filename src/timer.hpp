#pragma once

#include "types.hpp"

#include <chrono>
#include <ratio>

namespace Hal::Timer
{

template <typename Period> using Duration = std::chrono::duration<u64, Period>;

static constexpr std::intmax_t cpu_clock = 100000000;

u64 get_stm0_timestamp();

struct Clock
{
    using rep        = u64;
    using period     = std::ratio<1, cpu_clock>;
    using duration   = Duration<period>; // 10ns which is period for 100 Mhz clock speed
    using time_point = std::chrono::time_point<Hal::Timer::Clock>;

    static time_point now() noexcept
    {
        u64 timestamp = get_stm0_timestamp();
        return time_point{duration{timestamp}};
    }
};

} // namespace Hal::Timer