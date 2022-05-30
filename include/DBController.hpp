/**
 *
 *  @file DBController.hpp
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

#include <drogon/drogon.h>
#include "Herb.hpp"


class DBController
{
public:



    static void initDB();


    static void addHerb(const Herb herb);

    static std::optional<Herb> getHerbByModel(const std::string &model){
        return Instance()._getHerbByModel( model );
    }



private:

    static DBController& Instance();

    DBController();
    DBController(const DBController& root) = delete;
    DBController& operator=(const DBController&) = delete;


    void _initDb();
    void _addHerb(const Herb herb);
    std::optional<Herb> _getHerbByModel(const std::string &model);


};
