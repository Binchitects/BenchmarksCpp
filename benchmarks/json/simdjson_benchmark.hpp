#include <simdjson.h>
#include "benchmark.hpp"

static void BM_Parsing_yyjson(benchmark::State& state) {
    simdjson::ondemand::parser parser;
    for (auto _ : state) {
        simdjson::padded_string json_padded = simdjson::padded_string::load(json_data);
        auto doc = parser.iterate(json_padded);
        benchmark::DoNotOptimize(doc);
    }
}
BENCHMARK(BM_Parsing_yyjson);
