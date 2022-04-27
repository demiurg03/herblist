#pragma once


#include <filesystem>
#include <fstream>

#include <drogon/drogon.h>

#include <fmt/format.h>
#include <fmt/ranges.h>


#include <libzippp/libzippp.h>

#include <nlohmann/json.hpp>



#include "const.h"









void write(const std::string &data, const std::string &file);


struct Herb{
    std::string name;
    std::map<std::string,std::string> tr_name;
    std::map<std::string,std::string> tr_content_path;
};

class FileRemover{
public:

    FileRemover(const std::string_view path) : _path(path){

    }

    ~FileRemover(){
        namespace fs = std::filesystem;

        if( fs::exists( _path ) ){
            fs::remove( _path );
        }

    }

private:
    std::string _path;
};


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


