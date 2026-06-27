#include "RateLimitInterceptor.h"
#include <iostream>

RateLimitInterceptor::RateLimitInterceptor(std::shared_ptr<RateLimitManager> managerInstance) 
    : manager(managerInstance) {}

void RateLimitInterceptor::handleRequest(const std::string& clientIp) {
    
    RateLimitResult result = manager->checkAccess(clientIp);

    if (result.isAllowed) {
        std::cout << "[HTTP 200 OK] Request allowed for IP: " << clientIp 
                  << " | Tokens remaining: " << result.remainingTokens << "\n";
    } else {
        std::cout << "[HTTP 429 TOO MANY REQUESTS] Blocked IP: " << clientIp 
                  << " | Retry in: " << result.retryAfterMilliseconds << " ms\n";
    }
}