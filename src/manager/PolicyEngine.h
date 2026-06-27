#pragma once
#include <string>
#include <memory>
#include "../core/IRateLimitingStrategy.h"

class PolicyEngine {
public:
    // Factory method that dynamically builds the right algorithm based on the user
    static std::shared_ptr<IRateLimitingStrategy> createStrategyForClient(const std::string& clientIp);
};