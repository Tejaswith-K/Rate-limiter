// File: src/main.cpp
#include <iostream>
#include <memory>
#include <thread>
#include <chrono>
#include "manager/RateLimitManager.h"
#include "middleware/RateLimitInterceptor.h"

int main() {
    std::cout << "==================================================\n";
    std::cout << "   STARTING C++ API RATE LIMITER SIMULATION\n";
    std::cout << "==================================================\n\n";

    // 1. Initialize the central manager and the middleware gatekeeper
    auto manager = std::make_shared<RateLimitManager>();
    RateLimitInterceptor interceptor(manager);

    std::string clientIP = "192.168.1.99";

    // 2. Simulate a rapid burst of traffic (12 requests in a split second)
    // Remember: Our TokenBucket default is 10 max tokens!
    std::cout << "--- Phase 1: Simulating Rapid Traffic Burst ---\n";
    for (int i = 1; i <= 12; ++i) {
        std::cout << "Request #" << i << " -> ";
        interceptor.handleRequest(clientIP);
    }

    // 3. Wait for 1 second to let the Token Bucket refill naturally
    std::cout << "\n--- Phase 2: Sleeping for 1.2 Seconds (Allowing Token Refills) ---\n";
    std::this_thread::sleep_for(std::chrono::milliseconds(1200));

    // 4. Try making requests again after the refill period
    std::cout << "\n--- Phase 3: Post-Refill Traffic Check ---\n";
    std::cout << "Request #13 -> ";
    interceptor.handleRequest(clientIP);
    std::cout << "Request #14 -> ";
    interceptor.handleRequest(clientIP);

    std::cout << "\n==================================================\n";
    std::cout << "          SIMULATION COMPLETE\n";
    std::cout << "==================================================\n";

    return 0;
}