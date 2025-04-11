#pragma once

#include "benchmark_sfx.hpp"
#include <nlohmann/json.hpp>

static void BM_Parsing_nlohmann(benchmark::State& state, const std::string& data) {
    for (auto _ : state) {
        auto doc = nlohmann::json::parse(data);
        benchmark::DoNotOptimize(doc);
    }
}

struct NLohamannParsingBenchmarkRegistrar {
    NLohamannParsingBenchmarkRegistrar() {
        for (const auto& test_case : benchmark_data) {
            std::string name = test_case.first;
            std::string data = test_case.second;
            benchmark::RegisterBenchmark(("ParsingJson/"+name+"/nlohmann").c_str(), [&data](benchmark::State& state) {
                BM_Parsing_nlohmann(state, data);
            })->Iterations(iterations);
        }
    }
};

static NLohamannParsingBenchmarkRegistrar nlohmann_parsing;