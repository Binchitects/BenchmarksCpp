cmake_minimum_required(VERSION 3.10)

set(This BenchmarksCpp)

project(${This} C CXX)

set(CMAKE_C_STANDARD_REQUIRED 99)
set(CMAKE_CXX_STANDARD_REQUIRED 11)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

# Define third-party directory
set(THIRDPARTY_DIR ${CMAKE_BINARY_DIR}/third_party)

# Fetch simdjson
include(FetchContent)
FetchContent_Declare(
    benchmark
    GIT_REPOSITORY https://github.com/google/benchmark.git
    GIT_TAG v1.9.2
)

# Fetch Google Test (required by Google Benchmark)
FetchContent_Declare(
    googletest
    GIT_REPOSITORY https://github.com/google/googletest.git
    GIT_TAG v1.16.0
)

# Enable benchmark's CMake options
set(BENCHMARK_ENABLE_TESTING OFF CACHE BOOL "Disable benchmark tests" FORCE)
set(BENCHMARK_ENABLE_GTEST_TESTS OFF CACHE BOOL "Disable benchmark's internal tests" FORCE)

# Make them available
FetchContent_MakeAvailable(benchmark googletest)

# Fetch yyjson
FetchContent_Declare(
    yyjson
    GIT_REPOSITORY https://github.com/ibireme/yyjson.git
    GIT_TAG 0.10.0
)

# Fetch nlohmann json
FetchContent_Declare(
    nlohmann_json
    GIT_REPOSITORY https://github.com/nlohmann/json.git
    GIT_TAG v3.11.3
)

# Fetch nlohmann json
FetchContent_Declare(
    simdjson
    GIT_REPOSITORY https://github.com/simdjson/simdjson.git
    GIT_TAG v3.12.3
)

# Fetch rapid json
FetchContent_Declare(
    rapidjson
    GIT_REPOSITORY https://github.com/Tencent/rapidjson.git
    GIT_TAG v1.1.0
)
set(RAPIDJSON_BUILD_TESTS OFF CACHE BOOL "Disable RapidJSON Tests")
set(RAPIDJSON_BUILD_EXAMPLES OFF CACHE BOOL "Disable RapidJSON Examples")

# Finish fetches
FetchContent_MakeAvailable(yyjson nlohmann_json rapidjson)

# executable
add_executable(json_benchmark benchmarks/json/benchmark_json.cpp)

# headers
target_include_directories(json_benchmark PRIVATE ${nlohmann_json_SOURCE_DIR}/single_include)
target_include_directories(json_benchmark PRIVATE ${rapidjson_SOURCE_DIR}/include)
target_include_directories(json_benchmark PRIVATE ${simdjson_SOURCE_DIR}/include)

# link libraries
target_link_libraries(json_benchmark PRIVATE benchmark::benchmark yyjson)
