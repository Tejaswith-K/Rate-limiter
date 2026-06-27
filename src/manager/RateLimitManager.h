#pragma once

#include <string>
#include <unordered_map>
#include <memory>
#include <mutex>          
#include <shared_mutex>   
#include "../core/IRateLimitingStrategy.h"
#include "../core/RateLimitResult.h"

class RateLimitManager {
private:
    // Maps a client IP string to their personal rate limiter algorithm
    std::unordered_map<std::string, std::shared_ptr<IRateLimitingStrategy>> clientMap;
    
    // C++17 Read/Write Mutex for high-concurrency map access
    std::shared_mutex mapMutex;

public:
    RateLimitResult checkAccess(const std::string& clientId);
};