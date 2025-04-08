cmake_minimum_required(VERSION 3.30)

# Set policy to honor visibility properties for all target types
cmake_policy(SET CMP0063 NEW)

set(This BenchmarksCpp)

project(${This} C CXX)

set(CMAKE_C_STANDARD_REQUIRED 99)
set(CMAKE_CXX_STANDARD_REQUIRED 17)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

add_subdirectory(benchmarks)
