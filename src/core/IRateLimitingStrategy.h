#pragma once
#include "RateLimitResult.h"

class IRateLimitingStrategy {
public:
    // Virtual destructor is mandatory for C++ interfaces
    virtual ~IRateLimitingStrategy() = default;

    // Pure virtual method
    virtual RateLimitResult evaluate() = 0;
};