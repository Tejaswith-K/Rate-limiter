#pragma once

struct RateLimitResult {
    bool isAllowed;
    int remainingTokens;
    long retryAfterMilliseconds;

    // Constructor for easy object creation
    RateLimitResult(bool allowed, int remaining, long retry = 0)
        : isAllowed(allowed), remainingTokens(remaining), retryAfterMilliseconds(retry) {}
};