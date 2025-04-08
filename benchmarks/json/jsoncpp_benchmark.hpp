#pragma once

#include "benchmark_sfx.hpp"
#include <json/json.h>
#include <sstream>

static void BM_Parsing_jsoncpp(benchmark::State& state, const std::string& data) {
    for (auto _ : state) {
        Json::CharReaderBuilder builder;
        Json::Value root;
        std::string errs;
        std::istringstream iss(data);
        bool parsingSuccessful = Json::parseFromStream(builder, iss, &root, &errs);
        if (!parsingSuccessful) {
            state.SkipWithError("Failed to parse JSON");
            continue;
        }
        benchmark::DoNotOptimize(builder);
        benchmark::DoNotOptimize(root);
        benchmark::DoNotOptimize(errs);
        benchmark::DoNotOptimize(iss);
    }
}

struct JsonCppParsingBenchmarkRegistrar {
    JsonCppParsingBenchmarkRegistrar() {
        for (const auto& [name, data] : benchmark_data) {
            benchmark::RegisterBenchmark(("ParsingJson/"+name+"/jsoncpp").c_str(), [&data](benchmark::State& state) {
                BM_Parsing_jsoncpp(state, data);
            })->Iterations(iterations);
        }
    }
};

static JsonCppParsingBenchmarkRegistrar jsoncpp_parsing;