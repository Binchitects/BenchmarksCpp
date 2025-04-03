#include <benchmark/benchmark.h>
#include <iostream>
#include <string>

// Include JSON libraries
#include <yyjson/yyjson.h>
#include "simdjson.h"
#include "rapidjson/document.h"
#include "nlohmann/json.hpp"

// Sample JSON data
const std::string json_data = R"({"name": "John", "age": 30, "city": "New York"})";

// Benchmark yyjson
static void BM_Parsing_yyjson(benchmark::State& state) {
    for (auto _ : state) {
        yyjson_doc* doc = yyjson_read(json_data.c_str(), json_data.size(), 0);
        benchmark::DoNotOptimize(doc);
        yyjson_doc_free(doc);
    }
}
BENCHMARK(BM_Parsing_yyjson);

// Benchmark simdjson
static void BM_Parsing_simdjson(benchmark::State& state) {
    simdjson::dom::parser parser;
    for (auto _ : state) {
        auto doc = parser.parse(json_data);
        benchmark::DoNotOptimize(doc);
    }
}

BENCHMARK(BM_Parsing_simdjson);
BENCHMARK_MAIN();
