#pragma once

#include "benchmark_sfx.hpp"
#include <JsonBox.h>

static void BM_Parsing_JsonBox(benchmark::State& state, const std::string& data) {
    for (auto _ : state) {
        JsonBox::Value value;
        value.loadFromString(data);
        benchmark::DoNotOptimize(value);
    }
}

struct JsonBoxParsingBenchmarkRegistrar {
    JsonBoxParsingBenchmarkRegistrar() {
        for (const auto& [name, data] : benchmark_data) {
            benchmark::RegisterBenchmark(("ParsingJson/"+name+"/jsonbox").c_str(), [&data](benchmark::State& state) {
                BM_Parsing_JsonBox(state, data);
            })->Iterations(iterations);
        }
    }
};

static JsonBoxParsingBenchmarkRegistrar jsonbox_parsing;