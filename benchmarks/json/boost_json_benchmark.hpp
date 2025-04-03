#pragma once

// #include <boost/json/src.hpp>
// #include "benchmark.hpp"

// static void BM_Parsing_BoostJSON(benchmark::State& state) {
//     for (auto _ : state) {
//         boost::json::error_code ec;
//         auto doc = boost::json::parse(json_data, ec);
//         if (ec) {
//             state.SkipWithError("Failed to parse JSON");
//             continue;
//         }
//         benchmark::DoNotOptimize(doc);
//     }
// }
// BENCHMARK(BM_Parsing_BoostJSON)->Name("JSON_Parsing/boost_json"); 