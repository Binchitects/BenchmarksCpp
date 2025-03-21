cmake_minimum_required(VERSION 3.10)
project(BenchmarksCpp)

set(CMAKE_CXX_STANDARD 17)

# Add Google Benchmark
add_subdirectory(third_party/benchmark)

# Add yyjson
add_subdirectory(third_party/yyjson)

# Add include directory
include_directories(third_party/yyjson/include)

# Benchmark executable
add_executable(json_benchmark benchmarks/benchmark_json.cpp)

# Link Google Benchmark
target_link_libraries(json_benchmark benchmark::benchmark)
# Link yyjson to benchmark executable
target_link_libraries(json_benchmark yyjson)
