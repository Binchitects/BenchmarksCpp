#pragma once

#include "benchmark_sfx.hpp"
#include <JsonBox.h>

static void BM_Parsing_JsonBox(benchmark::State& state) {
    for (auto _ : state) {
        JsonBox::Value value;
        value.loadFromString(smal_flat_json);
        benchmark::DoNotOptimize(value);
    }
}
BENCHMARK(BM_Parsing_JsonBox)->Name("JSON_Parsing/jsonbox");
