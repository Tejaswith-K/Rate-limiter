#include "FixedWindowStrategy.h"

FixedWindowStrategy::FixedWindowStrategy(int maxRequests, long windowSizeInMilliseconds)
    : limit(maxRequests), currentCount(0), windowSizeMs(windowSizeInMilliseconds) {
    windowStartTime = std::chrono::steady_clock::now();
}

RateLimitResult FixedWindowStrategy::evaluate() {
    
    std::lock_guard<std::mutex> lock(mtx);
    
    auto now = std::chrono::steady_clock::now();
    auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(now - windowStartTime).count();

    if (elapsed >= windowSizeMs) {
        windowStartTime = now;
        currentCount = 0;
    }

    // Check if within limits
    if (currentCount < limit) {
        currentCount++;
        return RateLimitResult(true, limit - currentCount, 0);
    } else {
        long retryAfter = windowSizeMs - elapsed;
        return RateLimitResult(false, 0, retryAfter);
    }
}