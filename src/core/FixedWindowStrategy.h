#pragma once
#include "IRateLimitingStrategy.h"
#include <mutex>
#include <chrono>

class FixedWindowStrategy : public IRateLimitingStrategy {
private:
    int limit;
    int currentCount;
    long windowSizeMs;
    std::chrono::steady_clock::time_point windowStartTime;
    
    std::mutex mtx; // Protects data in multithreaded environments

public:
    FixedWindowStrategy(int maxRequests, long windowSizeInMilliseconds);
    RateLimitResult evaluate() override;
};