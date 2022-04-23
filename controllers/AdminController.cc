#include "AdminController.h"

void AdminController::render(const drogon::HttpRequestPtr &req, std::function<void (const drogon::HttpResponsePtr &)> &&callback){
    using namespace drogon;

    if( !isCorrectAddress(req)  ){

        auto resp = HttpResponse::newRedirectionResponse("404",HttpStatusCode::k404NotFound);
        return;
    }

    HttpViewData data;

    auto resp = HttpResponse::newHttpViewResponse("adminPage.csp", data);

    callback(resp);

}

void AdminController::upload(const drogon::HttpRequestPtr &req, std::function<void (const drogon::HttpResponsePtr &)> &&callback){
    using namespace drogon;

    if( !isCorrectAddress(req)  ){

        auto resp = HttpResponse::newRedirectionResponse("404",HttpStatusCode::k404NotFound);
        return;
    }

    MultiPartParser fileUpload;

    if (fileUpload.parse(req) != 0 || fileUpload.getFiles().size() == 0) {

        auto resp = HttpResponse::newHttpResponse();
        resp->setBody("error");
        resp->setStatusCode(k403Forbidden);
        callback(resp);
        return;

    }

    auto &file = fileUpload.getFiles()[0];


    file.save();


    if ( !fileWork("uploads/" + file.getFileName())){

    }

    callback(HttpResponse::newHttpResponse());
}

#include <fstream>

void write(const std::string &data, const std::string &file){
std::ofstream files(file);

files << data;




}


struct Herb{
    std::string name;
    std::map<std::string,std::string> tr_name;
    std::map<std::string,std::string> tr_content;
};



std::pair<bool, std::size_t> zipFileExist(const std::string &file, const std::vector<libzippp::ZipEntry>& vze ){

    std::size_t i = 0;

    for(const auto &it :vze){
        if(it.getName() == file){

            return {true, i};


        }

        i++;
    }

    return {false,0};
}


bool AdminController::fileWork(const std::string &stringPath){
    namespace fs = std::filesystem;

    fs::path path(stringPath);


    LOG_INFO << "Upload new file : " << path;


    using namespace libzippp;

    libzippp::ZipArchive zf(path.c_str());
    zf.open(libzippp::ZipArchive::ReadOnly);



    const auto et = zf.getEntries();

    std::string rootDir = et.at(0).getName();

    rootDir = rootDir.substr(0, rootDir.find('/')+1);

    std::string jsonPath = rootDir+"config.json";






    auto jsonDoc =  nlohmann::json::parse(et.at(zipFileExist(jsonPath, et).second).readAsText());

    Herb herb;


    herb.name = jsonDoc["name"];

    for(const auto &it: jsonDoc["tr_content"]){
        std::string lang = it["lang"];
        std::string filePath = it["file"];


        herb.tr_content.insert({lang,filePath});
    }


    for(const auto &it: jsonDoc["tr_name"]){
        std::string lang = it["lang"];
        std::string name = it["name"];

        herb.tr_name.insert({lang,name});
    }



    fs::create_directory("static/" + herb.name);


    for(const auto &it : herb.tr_content){
        const auto fileName =  it.second;
        const auto zipFileName = rootDir+it.second;

        std::string path =  "static/"+herb.name+"/"+it.second;




        write(et.at(zipFileExist(zipFileName, et).second).readAsText(), path);


    }




    fs::remove(stringPath);

    return true;
}

bool AdminController::isCorrectAddress(const drogon::HttpRequestPtr &req){

    const auto ip = req->getLocalAddr().toIp();

    if( ip == "127.0.0.1" )
        return true;

    return false;
}
