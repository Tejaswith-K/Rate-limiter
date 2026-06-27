#include "RateLimitManager.h"
#include "PolicyEngine.h" 

RateLimitResult RateLimitManager::checkAccess(const std::string& clientId) {
    std::shared_ptr<IRateLimitingStrategy> strategy;

    {
        std::shared_lock<std::shared_mutex> readLock(mapMutex);
        auto it = clientMap.find(clientId);
        if (it != clientMap.end()) {
            strategy = it->second;
        }
    }

    if (!strategy) {
        std::unique_lock<std::shared_mutex> writeLock(mapMutex);
        auto it = clientMap.find(clientId);
        if (it == clientMap.end()) {
            
            // --- THE UPGRADE IS HERE ---
            // The Manager no longer cares about the math. It delegates to the Policy Engine.
            strategy = PolicyEngine::createStrategyForClient(clientId);
            clientMap[clientId] = strategy;
            
        } else {
            strategy = it->second;
        }
    }

    return strategy->evaluate();
}