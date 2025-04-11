#pragma once

#include "benchmark_sfx.hpp"
#include <simdjson.h>

static void BM_Parsing_simdjson(benchmark::State& state, const std::string& data) {
    for (auto _ : state) {
        simdjson::ondemand::parser parser;
        simdjson::padded_string json_padded(data);
        auto doc = parser.iterate(json_padded);
        if (doc.error()) {
            state.SkipWithError("Failed to parse JSON");
            continue;
        }
        benchmark::DoNotOptimize(parser);
        benchmark::DoNotOptimize(json_padded);
        benchmark::DoNotOptimize(doc);
    }
}

struct SIMDJsonParsingBenchmarkRegistrar {
    SIMDJsonParsingBenchmarkRegistrar() {
        for (const auto& test_case : benchmark_data) {
            std::string name = test_case.first;
            std::string data = test_case.second;
            benchmark::RegisterBenchmark(("ParsingJson/"+name+"/simdjson").c_str(), [&data](benchmark::State& state) {
                BM_Parsing_simdjson(state, data);
            })->Iterations(iterations);
        }
    }
};

static SIMDJsonParsingBenchmarkRegistrar simdjson_parsing;