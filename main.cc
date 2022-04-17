﻿/*
MIT License

Copyright (c) 2022 Maxim Palshin

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

#include <filesystem>
#include <iostream>
#include <chrono>



#include <drogon/drogon.h>

#include <nlohmann/json.hpp>


class AdminController : public drogon::HttpController<AdminController>
{




public:

    PATH_LIST_BEGIN

    ADD_METHOD_TO(AdminController::render,"admin/", drogon::Get);
    PATH_LIST_END


    void render(const drogon::HttpRequestPtr &req,  std::function<void(const drogon::HttpResponsePtr &)> &&callback){
        using namespace drogon;

        if( !isCorrectAddress(req)  ){

            auto resp = HttpResponse::newRedirectionResponse("404",HttpStatusCode::k404NotFound);
            return;
        }


        auto resp = HttpResponse::newHttpResponse();
        resp->setBody("<p>Hello, world!</p>");
        resp->setExpiredTime(0);
        callback(resp);

    }


    bool isCorrectAddress(const drogon::HttpRequestPtr &req){

        const auto ip = req->getLocalAddr().toIp();

        if( ip == "127.0.0.1" )
            return true;

        return false;
    }


};




int main() {

    std::setlocale(LC_ALL, "");



    drogon::app().loadConfigFile("config.json");


    drogon::app().setStaticFileHeaders( { {"font","font"}, {"herb", "herb"}}  );


    drogon::app().run();



    return EXIT_SUCCESS;
}