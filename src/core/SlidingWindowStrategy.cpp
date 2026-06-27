#include "SlidingWindowStrategy.h"

SlidingWindowStrategy::SlidingWindowStrategy(int maxRequests, long windowSizeInMilliseconds)
    : limit(maxRequests), windowSizeMs(windowSizeInMilliseconds) {}

RateLimitResult SlidingWindowStrategy::evaluate() {
    std::lock_guard<std::mutex> lock(mtx);
    
    auto now = std::chrono::steady_clock::now();
    auto windowStart = now - std::chrono::milliseconds(windowSizeMs);

    // 1. Evict all expired timestamps from the front of the queue
    while (!requestLog.empty() && requestLog.front() < windowStart) {
        requestLog.pop_front();
    }

    // 2. Check if we have room in the current rolling window
    if (requestLog.size() < limit) {
        requestLog.push_back(now); // Log this exact request time
        return RateLimitResult(true, limit - requestLog.size(), 0);
    } else {
        // 3. Block and calculate exactly when the oldest request will expire
        auto oldestRequest = requestLog.front();
        auto expirationTime = oldestRequest + std::chrono::milliseconds(windowSizeMs);
        long retryAfter = std::chrono::duration_cast<std::chrono::milliseconds>(expirationTime - now).count();
        
        return RateLimitResult(false, 0, retryAfter);
    }
}