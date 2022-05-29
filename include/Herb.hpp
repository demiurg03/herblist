#pragma once
#include <string>
#include <optional>

#include <jsoncpp/json/value.h>

struct Herb{
    std::optional<std::size_t> id;
    std::string name;
    std::string model;
    std::string content;
};




Herb jsonToHerb(const Json::Value &value );
