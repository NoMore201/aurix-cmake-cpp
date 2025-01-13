#pragma once

#include <cstdlib>

#define LIKELY(x) __builtin_expect(!!(x), 1)

// TODO: add error logging
#define VERIFY(cond) (LIKELY(cond) ? static_cast<void>(0) : std::abort())

#define VERIFY_NOT_REACHED() VERIFY(false)