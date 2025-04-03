cmake_minimum_required(VERSION 3.10)

set(This BenchmarksCpp)

project(${This} C CXX)

set(CMAKE_C_STANDARD_REQUIRED 99)
set(CMAKE_CXX_STANDARD_REQUIRED 11)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

# Add Google Benchmark
add_subdirectory(third_party/benchmark)

# Add json libraries
add_subdirectory(third_party/json/nlohmann)
add_subdirectory(third_party/json/rapidjson)
add_subdirectory(third_party/json/sajson)
add_subdirectory(third_party/json/simdjson)
add_subdirectory(third_party/json/yyjson)

# Add json include directory
include_directories(third_party/yyjson/include)

# Benchmark executable
add_executable(json_benchmark benchmarks/benchmark_json.cpp)

# Link Google Benchmark
target_link_libraries(json_benchmark benchmark::benchmark)
# Link yyjson to benchmark executable
target_link_libraries(json_benchmark yyjson)
