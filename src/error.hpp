#pragma once

#include <exception>

#define LIKELY(x) __builtin_expect(!!(x), 1)

// TODO: implement properly
#define VERIFY(cond) (LIKELY(cond) ? static_cast<void>(0) : std::terminate())

#define VERIFY_NOT_REACHED() std::terminate()