/**
 *
 *  @file Cache.cpp
 *  @author Maxim Palshin
 *
 *  Copyright 2022, Maxim Palshin.  All rights reserved.
 *  Use of this source code is governed by a MIT license
 *  that can be found in the License file.
 *
 *  herblist
 *
 */




#include "Cache.hpp"


void Cache::remove(const std::size_t id){
    _data.erase( id );
}

void Cache::change(const Herb &herb){
    _data[herb.id.value()] = herb;
}

void Cache::clear(){
    _data.clear();
}

Herb Cache::at(const std::size_t id){
    return _data.at(id);
}

Herb Cache::at(const std::string model){
    return std::find_if(_data.begin(), _data.end(), [&model](auto elm){ return elm.second.model == model;})->second;
}

bool Cache::contains(const std::size_t id) const{
    return _data.find(id) != _data.end();
}

bool Cache::contains(const std::string model) const{
    return (std::find_if(_data.begin(), _data.end(), [&model](auto elm){ return  elm.second.model == model;}) != _data.end());
}
