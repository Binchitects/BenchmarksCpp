#pragma once

#include "benchmark_sfx.hpp"
#include <yyjson.h>

static void BM_Parsing_yyjson(benchmark::State& state) {
    for (auto _ : state) {
        yyjson_doc* doc = yyjson_read(smal_flat_json.c_str(), smal_flat_json.size(), YYJSON_READ_NOFLAG);
        benchmark::DoNotOptimize(doc);
        yyjson_doc_free(doc);
    }
}
BENCHMARK(BM_Parsing_yyjson)->Name("JSON_Parsing/yyjson");
