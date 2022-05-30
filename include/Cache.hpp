/**
 *
 *  @file Cache.hpp
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

#include <map>
#include <algorithm>

#include "Herb.hpp"


class Cache{


public:


    void remove(const std::size_t id);

    void change(const Herb &herb);

    void clear();

    Herb at(const std::size_t id);
    Herb at(const std::string model);



    bool contains(const std::size_t id)const;


    bool contains(const std::string model)const;


private:
    std::map<std::size_t, Herb> _data;
};
