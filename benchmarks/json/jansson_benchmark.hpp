#pragma once

#include "benchmark_sfx.hpp"
#include <jansson.h>

static void BM_Parsing_Jansson(benchmark::State& state, const std::string& data) {
    for (auto _ : state) {
        json_error_t error;
        json_t* root = json_loads(data.c_str(), 0, &error);
        benchmark::DoNotOptimize(root);
        json_decref(root);
    }
}

struct JanssonParsingBenchmarkRegistrar {
    JanssonParsingBenchmarkRegistrar() {
        for (const auto& [name, data] : benchmark_data) {
            benchmark::RegisterBenchmark(("ParsingJson/"+name+"/jansson").c_str(), [data](benchmark::State& state) {
                BM_Parsing_Jansson(state, data);
            })->Iterations(iterations);
        }
    }
};

static JanssonParsingBenchmarkRegistrar jansson_parsing;