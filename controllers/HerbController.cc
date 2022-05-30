/**
 *
 *  @file HerbController.cpp
 *  @author Maxim Palshin
 *
 *  Copyright 2022, Maxim Palshin.  All rights reserved.
 *  Use of this source code is governed by a MIT license
 *  that can be found in the License file.
 *
 *  herblist
 *
 */



#include "HerbController.h"

void HerbController::renderHerber( [[maybe_unused]]  const drogon::HttpRequestPtr &req, Callback callback, const std::string& herbModel) {
    using namespace drogon;


    const auto item = DBController::getHerbByModel(herbModel);

    if( !item.has_value() ){

        auto resp = HttpResponse::newRedirectionResponse("404",HttpStatusCode::k404NotFound);

        return;
    }

    const auto itemValue = item.value();

    HttpViewData data;


    data.insert("title", itemValue.name);
    data.insert("body", itemValue.content);

    auto resp = HttpResponse::newHttpViewResponse("herbPage.csp", data);



    callback(resp);




}



void HerbController::render(const drogon::HttpRequestPtr &req, Callback callback){


    std::stringstream html;

   const auto herbs = DBController::getAllHerb();
       for ( const auto &herb : herbs ) {

           const auto name = herb.name;
           const auto model = herb.model;

           html << R"(<p><a href="/herb/)" <<  model << "\">" << name  << "</a></p>";

       }



       auto resp = drogon::HttpResponse::newHttpResponse();

       resp->setBody( html.str() );

       callback(resp);


}



