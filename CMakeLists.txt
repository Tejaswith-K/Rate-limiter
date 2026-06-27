cmake_minimum_required(VERSION 3.14)
project(CppRateLimiter VERSION 1.0 LANGUAGES CXX)

# Force modern C++17 rules (needed for std::shared_mutex)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Gather all source files across directories
set(SOURCES
    src/main.cpp
    src/core/TokenBucketStrategy.cpp
    src/core/FixedWindowStrategy.cpp
    src/core/SlidingWindowStrategy.cpp  
    src/manager/RateLimitManager.cpp
    src/manager/PolicyEngine.cpp         
    src/middleware/RateLimitInterceptor.cpp
)

# Declare our executable binary target
add_executable(rate_limiter ${SOURCES})

# Target standard OS thread libraries (pthread/winthreads) natively
find_package(Threads REQUIRED)
target_link_libraries(rate_limiter PRIVATE Threads::Threads)