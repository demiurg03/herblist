/**
 *
 *  @file Herb.cpp
 *  @author Maxim Palshin
 *
 *  Copyright 2022, Maxim Palshin.  All rights reserved.
 *  Use of this source code is governed by a MIT license
 *  that can be found in the License file.
 *
 *  herblist
 *
 */


#include "Herb.hpp"





Herb jsonToHerb(const Json::Value &value){

    Herb herb;


    if (  value.isMember("id") ){

        auto idJson = value.get("id", "-" );

        if( idJson.isUInt64() ){
            herb.id = idJson.asUInt64();
        }


    }


    herb.name = value["herbHame"].asString();
    herb.model = value["herbModel"].asString();
    herb.content = value["herbContent"].asString();





    return herb;
}
