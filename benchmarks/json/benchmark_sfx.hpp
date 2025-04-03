#pragma once

#include <string>
#include <benchmark/benchmark.h>

const std::string smal_flat_json = R"({"name":"John","age":30,"city":"New York"})";
const std::string smal_flat_json_indented = R"({
    "name":"John",
    "age":30,
    "city":"New York"
})";

const std::string small_nested_json = R"({"name":"John","age":30,"city":"New York","team":{"name":"math","department":{"name":"science"}}})";
const std::string small_nested_json_indented = R"({
    "name":"John",
    "age":30,
    "city":"New York",
    "team":{
        "name":"math",
        "department":{
            "name":"science"
        }
    }
})";
