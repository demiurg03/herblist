#pragma once


#include <filesystem>
#include <fstream>

#include <drogon/drogon.h>

#include "const.h"
#include "Herb.hpp"
#include "DBController.hpp"





class AdminController : public drogon::HttpController<AdminController>
{




public:

    PATH_LIST_BEGIN

    ADD_METHOD_TO(AdminController::render,"admin/", drogon::Get);
    ADD_METHOD_TO(AdminController::upload,"admin/upload", drogon::Get);
    ADD_METHOD_TO(AdminController::addHerb,"admin/addHerb", drogon::Post);

    PATH_LIST_END


    void render(const drogon::HttpRequestPtr &req,  std::function<void(const drogon::HttpResponsePtr &)> &&callback);

    void upload(const drogon::HttpRequestPtr &req,  std::function<void(const drogon::HttpResponsePtr &)> &&callback);

    void addHerb(const drogon::HttpRequestPtr &req,  std::function<void(const drogon::HttpResponsePtr &)> &&callback);



    bool isCorrectAddress(const drogon::HttpRequestPtr &req);


};


