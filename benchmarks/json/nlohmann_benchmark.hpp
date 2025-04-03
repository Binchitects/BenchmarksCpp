#include "benchmark.hpp"
#include <nlohmann/json.hpp>

// Benchmark nlohmann JSON
static void BM_Parsing_nlohmann(benchmark::State& state) {
    for (auto _ : state) {
        auto doc = nlohmann::json::parse(json_data);
        benchmark::DoNotOptimize(doc);
    }
}
BENCHMARK(BM_Parsing_nlohmann);
