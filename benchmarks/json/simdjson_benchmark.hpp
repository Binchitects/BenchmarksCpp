#pragma once

#include "benchmark_sfx.hpp"
#include <simdjson.h>

static void BM_Parsing_simdjson(benchmark::State& state) {
    simdjson::ondemand::parser parser;
    
    for (auto _ : state) {
        simdjson::padded_string json_padded(smal_flat_json);
        auto doc = parser.iterate(json_padded);
        if (doc.error()) {
            state.SkipWithError("Failed to parse JSON");
            continue;
        }
        benchmark::DoNotOptimize(doc);
    }
}
BENCHMARK(BM_Parsing_simdjson)->Name("JSON_Parsing/simdjson");
