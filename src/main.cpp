/**
 *
 *  @file main.cpp
 *  @author Maxim Palshin
 *
 *  Copyright 2022, Maxim Palshin.  All rights reserved.
 *  Use of this source code is governed by a MIT license
 *  that can be found in the License file.
 *
 *  herblist
 *
 */

#include <iostream>
#include <chrono>
#include <filesystem>


#include <drogon/drogon.h>

#include <nlohmann/json.hpp>


#include "const.h"
#include "DBController.hpp"

int main() {


    if constexpr(gv_isDebug){
        LOG_INFO << "start is debug mode";
    }

    if( !std::filesystem::exists("static") ){
         std::filesystem::create_directory("static");
    }



    std::setlocale(LC_ALL, "");



    drogon::app().loadConfigFile("config.json");


    drogon::app().setStaticFileHeaders( { {"static", "static"} }  );
    drogon::app().setUploadPath("uploads");





    drogon::app().run();

        DBController::initDB();

    return EXIT_SUCCESS;
}
