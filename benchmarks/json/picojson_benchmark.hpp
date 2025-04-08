#pragma once

#include "benchmark_sfx.hpp"
#include <picojson.h>

static void BM_Parsing_Picojson(benchmark::State& state, const std::string& data) {
    for (auto _ : state) {
        picojson::value v;
        std::string err = picojson::parse(v, data);
        benchmark::DoNotOptimize(v);
    }
}

struct PicojsonParsingBenchmarkRegistrar {
    PicojsonParsingBenchmarkRegistrar() {
        for (const auto& [name, data] : benchmark_data) {
            benchmark::RegisterBenchmark(("ParsingJson/"+name+"/picojson").c_str(), [&data](benchmark::State& state) {
                BM_Parsing_Picojson(state, data);
            })->Iterations(iterations);
        }
    }
};

static PicojsonParsingBenchmarkRegistrar picojson_parsing;