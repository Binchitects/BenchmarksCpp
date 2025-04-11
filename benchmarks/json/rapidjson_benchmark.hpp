#pragma once

#include "benchmark_sfx.hpp"
#include <rapidjson/document.h>

static void BM_Parsing_RapidJSON(benchmark::State& state, const std::string& data) {
    for (auto _ : state) {
        const char* json = data.c_str();
        rapidjson::Document doc;
        doc.Parse(json);
        if (doc.HasParseError()) {
            state.SkipWithError("Failed to parse JSON");
            continue;
        }
        benchmark::DoNotOptimize(json);
        benchmark::DoNotOptimize(doc);
    }
}

struct RapidJSONParsingBenchmarkRegistrar {
    RapidJSONParsingBenchmarkRegistrar() {
        for (const auto& test_case : benchmark_data) {
            std::string name = test_case.first;
            std::string data = test_case.second;
            benchmark::RegisterBenchmark(("ParsingJson/"+name+"/rapidjson").c_str(), [&data](benchmark::State& state) {
                BM_Parsing_RapidJSON(state, data);
            })->Iterations(iterations);
        }
    }
};

static RapidJSONParsingBenchmarkRegistrar rapidjson_parsing;