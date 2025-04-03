#include <benchmark/benchmark.h>
#include <iostream>
#include <string>

// Include JSON libraries
#include <yyjson.h>

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

BENCHMARK_MAIN();
