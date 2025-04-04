#pragma once

#include "benchmark_sfx.hpp"
#include <yyjson.h>

static void BM_Parsing_yyjson(benchmark::State& state, const std::string& data) {
    for (auto _ : state) {
        yyjson_doc* doc = yyjson_read(data.c_str(), data.size(), YYJSON_READ_NOFLAG);
        benchmark::DoNotOptimize(doc);
        yyjson_doc_free(doc);
    }
}

struct YYJsonParsingBenchmarkRegistrar {
    YYJsonParsingBenchmarkRegistrar() {
        for (const auto& [name, data] : benchmark_data) {
            benchmark::RegisterBenchmark(("ParsingJson/"+name+"/yyjson").c_str(), [data](benchmark::State& state) {
                BM_Parsing_yyjson(state, data);
            })->Iterations(iterations);
        }
    }
};

static YYJsonParsingBenchmarkRegistrar yyjson_parsing;