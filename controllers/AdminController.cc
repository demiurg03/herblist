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


class HerbParserFromZip{
public:

    HerbParserFromZip(libzippp::ZipArchive &zip) : _zip(zip){

    }


    Herb parse(){







    }





private:
    libzippp::ZipArchive &_zip;


    //FIXME: notWork
    std::size_t _countHerb(){
        const auto fileList = _zip.getEntries();

        const auto count = 1ul;

        for(const auto &file : fileList){

            if( !file.isDirectory() ){
                continue;
            }

            const auto fname = file.getName();


        }



        return count;
    }





};

bool AdminController::fileWork(const std::string &stringPath){
    namespace fs = std::filesystem;
    using namespace libzippp;


    fs::path path(stringPath);


    LOG_INFO << "Upload new file : " << path;


    FileRemover fr(path.c_str());


    ZipArchive zf(path.c_str());
    zf.open(libzippp::ZipArchive::ReadOnly);

    HerbParserFromZip parser(zf);
    auto herb =  parser.parse();


    return true;
}

bool AdminController::isCorrectAddress(const drogon::HttpRequestPtr &req){


    if constexpr(gv_isDebug){
        return true;
    }

    const auto ip = req->getLocalAddr().toIp();

    if( ip == "127.0.0.1" )
        return true;

    return false;
}

void write(const std::string &data, const std::string &file){
    std::ofstream files(file);

    files << data;




}

std::pair<bool, std::size_t> zipFileExist(const std::string &file, const std::vector<libzippp::ZipEntry> &vze){

    std::size_t i = 0;

    for(const auto &it :vze){
        if(it.getName() == file){

            return {true, i};


        }

        i++;
    }

    return {false, 0};
}
