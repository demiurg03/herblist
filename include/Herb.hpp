/**
 *
 *  @file Herb.hpp
 *  @author Maxim Palshin
 *
 *  Copyright 2022, Maxim Palshin.  All rights reserved.
 *  Use of this source code is governed by a MIT license
 *  that can be found in the License file.
 *
 *  herblist
 *
 */


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
