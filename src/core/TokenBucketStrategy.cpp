#include "TokenBucketStrategy.h"
#include <algorithm>

TokenBucketStrategy::TokenBucketStrategy(int capacity, int refillRatePerSecond) {
    maxTokens = capacity;
    currentTokens = capacity;
    refillRatePerMs = refillRatePerSecond / 1000.0;
    lastRefillTime = std::chrono::steady_clock::now();
}

void TokenBucketStrategy::refill() {
    auto now = std::chrono::steady_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(now - lastRefillTime).count();
    
    // Calculate how many tokens to add based on exact milliseconds passed
    int tokensToAdd = duration * refillRatePerMs;
    
    if (tokensToAdd > 0) {
        currentTokens = std::min(maxTokens, currentTokens + tokensToAdd);
        lastRefillTime = now; 
    }
}

RateLimitResult TokenBucketStrategy::evaluate() {
    std::lock_guard<std::mutex> lock(mtx);
    
    refill(); // Lazily calculate refills before checking

    if (currentTokens > 0) {
        currentTokens--;
        return RateLimitResult(true, currentTokens, 0);
    } else {
        long retryAfter = (1.0 / refillRatePerMs); // Milliseconds until 1 token generates
        return RateLimitResult(false, 0, retryAfter);
    }
}