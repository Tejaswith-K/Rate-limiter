#include "PolicyEngine.h"
#include "../core/SlidingWindowStrategy.h"
#include "../core/TokenBucketStrategy.h"
#include "../core/FixedWindowStrategy.h"

std::shared_ptr<IRateLimitingStrategy> PolicyEngine::createStrategyForClient(const std::string& clientIp) {
    // Simulated Business Logic: Route based on IP prefixes or client tiers
    
    // Example: Internal Company Network gets massive Token Bucket limits
    if (clientIp.rfind("10.0.", 0) == 0) { 
        return std::make_shared<TokenBucketStrategy>(1000, 500);
    }
    
    // Example: Premium Users (simulated by a specific IP) get the precise Sliding Window
    if (clientIp == "192.168.1.99") {
        return std::make_shared<SlidingWindowStrategy>(50, 1000); // 50 requests per second
    }
    
    // Example: Default/Free tier gets a strict, low-memory Fixed Window
    return std::make_shared<FixedWindowStrategy>(5, 1000); // 5 requests per second
}