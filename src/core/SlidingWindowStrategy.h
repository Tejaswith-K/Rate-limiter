#pragma once
#include "IRateLimitingStrategy.h"
#include <mutex>
#include <chrono>
#include <deque>

class SlidingWindowStrategy : public IRateLimitingStrategy {
private:
    int limit;
    long windowSizeMs;
    // Stores the exact timestamp of every valid request
    std::deque<std::chrono::steady_clock::time_point> requestLog;
    
    std::mutex mtx;

public:
    SlidingWindowStrategy(int maxRequests, long windowSizeInMilliseconds);
    RateLimitResult evaluate() override;
};