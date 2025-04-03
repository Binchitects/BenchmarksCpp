#pragma once

#include "benchmark_sfx.hpp"
#include <json/json.h>
#include <sstream>

static void BM_Parsing_jsoncpp(benchmark::State& state) {
    Json::CharReaderBuilder builder;
    Json::Value root;
    std::string errs;
    
    for (auto _ : state) {
        std::istringstream iss(smal_flat_json);
        bool parsingSuccessful = Json::parseFromStream(builder, iss, &root, &errs);
        if (!parsingSuccessful) {
            state.SkipWithError("Failed to parse JSON");
            continue;
        }
        benchmark::DoNotOptimize(root);
    }
}

BENCHMARK(BM_Parsing_jsoncpp)->Name("JSON_Parsing/jsoncpp"); 