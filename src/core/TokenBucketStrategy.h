#pragma once
#include "IRateLimitingStrategy.h"
#include <mutex>
#include <chrono>

class TokenBucketStrategy : public IRateLimitingStrategy {
private:
    int maxTokens;
    int currentTokens;
    double refillRatePerMs;
    std::chrono::steady_clock::time_point lastRefillTime;
    
    std::mutex mtx;

    void refill();

public:
    TokenBucketStrategy(int capacity, int refillRatePerSecond);
    RateLimitResult evaluate() override;
};