#pragma once

#include "benchmark_sfx.hpp"
#include <rapidjson/document.h>

static void BM_Parsing_RapidJSON(benchmark::State& state) {
    const char* json = json_data.c_str();
    for (auto _ : state) {
        rapidjson::Document doc;
        doc.Parse(json);
        if (doc.HasParseError()) {
            state.SkipWithError("Failed to parse JSON");
            continue;
        }
        benchmark::DoNotOptimize(doc);
    }
}
BENCHMARK(BM_Parsing_RapidJSON)->Name("JSON_Parsing/rapidjson");
