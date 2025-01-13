#pragma once

#include "types.hpp"

#include <chrono>
#include <ratio>

namespace Hal::Timer {

// TODO: define clock
using Duration = std::chrono::duration<u64, std::nano>;

// TODO: refactor when clock implemented
u64 now();

bool elapsed(auto duration, u64 start_time) {
    auto nanoseconds = std::chrono::duration_cast<std::chrono::nanoseconds>(duration);
    auto current_time = now();
    return current_time - start_time > static_cast<u64>(nanoseconds.count());
}

} // namespace Hal::Timer