#pragma once


#include <filesystem>

#include <drogon/drogon.h>

class AdminController : public drogon::HttpController<AdminController>
{




public:

    PATH_LIST_BEGIN

    ADD_METHOD_TO(AdminController::render,"admin/", drogon::Get);
    ADD_METHOD_TO(AdminController::upload,"admin/upload", drogon::Post);

    PATH_LIST_END


    void render(const drogon::HttpRequestPtr &req,  std::function<void(const drogon::HttpResponsePtr &)> &&callback);

    void upload(const drogon::HttpRequestPtr &req,  std::function<void(const drogon::HttpResponsePtr &)> &&callback);


    bool fileWork(const std::string &stringPath);


    bool isCorrectAddress(const drogon::HttpRequestPtr &req);


};


