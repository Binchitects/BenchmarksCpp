#pragma once

#include "benchmark_sfx.hpp"
#include <picojson.h>

static void BM_Parsing_Picojson(benchmark::State& state) {
    for (auto _ : state) {
        picojson::value v;
        std::string err = picojson::parse(v, smal_flat_json);
        benchmark::DoNotOptimize(v);
    }
}
BENCHMARK(BM_Parsing_Picojson)->Name("JSON_Parsing/Picojson");