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

bool AdminController::fileWork(const std::string &stringPath){
    namespace fs = std::filesystem;

    fs::path path(stringPath);


    LOG_INFO << "Upload new file : " << path;


    std::filesystem::remove(path);

    return true;
}

bool AdminController::isCorrectAddress(const drogon::HttpRequestPtr &req){

    const auto ip = req->getLocalAddr().toIp();

    if( ip == "127.0.0.1" )
        return true;

    return false;
}
