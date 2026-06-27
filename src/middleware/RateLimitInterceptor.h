#pragma once

#include <string>
#include <memory>
#include "../manager/RateLimitManager.h"

class RateLimitInterceptor {
private:
    std::shared_ptr<RateLimitManager> manager;

public:
    // Dependency Injection: Pass the manager in via constructor
    RateLimitInterceptor(std::shared_ptr<RateLimitManager> managerInstance);
    
    // Simulates an incoming HTTP Request
    void handleRequest(const std::string& clientIp);
};