cmake_minimum_required(VERSION 3.11)

# Set policy to honor visibility properties for all target types
cmake_policy(SET CMP0063 NEW)

set(This BenchmarksCpp)

project(${This} C CXX)

set(CMAKE_C_STANDARD_REQUIRED 99)
set(CMAKE_CXX_STANDARD_REQUIRED 14)
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

# Fetch simdjson
FetchContent_Declare(
    simdjson
    GIT_REPOSITORY https://github.com/simdjson/simdjson.git
    GIT_TAG v3.12.3
)

# Fetch rapid json
FetchContent_Declare(
    rapidjson
    GIT_REPOSITORY https://github.com/Tencent/rapidjson.git
    GIT_TAG master
)
set(RAPIDJSON_BUILD_TESTS OFF CACHE BOOL "Disable RapidJSON Tests")
set(RAPIDJSON_BUILD_EXAMPLES OFF CACHE BOOL "Disable RapidJSON Examples")
set(RAPIDJSON_HAS_STDSTRING ON CACHE BOOL "Enable std::string support")
set(RAPIDJSON_NOMEMBERITERATORCLASS ON CACHE BOOL "Disable member iterator class")

# Fetch JsonBox
FetchContent_Declare(
    jsonbox
    GIT_REPOSITORY https://github.com/anhero/JsonBox.git
    GIT_TAG 0.6.2
)

# Fetch jsoncpp
FetchContent_Declare(
    jsoncpp
    GIT_REPOSITORY https://github.com/open-source-parsers/jsoncpp.git
    GIT_TAG 1.9.5
)

# Fetch picojson
FetchContent_Declare(
    picojson
    GIT_REPOSITORY https://github.com/kazuho/picojson.git
    GIT_TAG v1.3.0
)

# Finish fetches
FetchContent_MakeAvailable(yyjson nlohmann_json rapidjson jsonbox simdjson jsoncpp picojson)

# executable
add_executable(json_benchmark benchmarks/json/benchmark_json.cpp)

# headers
target_include_directories(json_benchmark PRIVATE ${nlohmann_json_SOURCE_DIR}/single_include)
target_include_directories(json_benchmark PRIVATE ${rapidjson_SOURCE_DIR}/include)
target_include_directories(json_benchmark PRIVATE ${jsoncpp_SOURCE_DIR}/include)
target_include_directories(json_benchmark PRIVATE ${picojson_SOURCE_DIR})

# link libraries
target_link_libraries(json_benchmark PRIVATE benchmark::benchmark yyjson JsonBox simdjson jsoncpp_lib)
