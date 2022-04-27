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
        Herb herb;
        auto zipEntries = _zip.getEntries();
        const auto rootPath = _getRootName(zipEntries);
        const auto jsonPath = _getJsonPath(zipEntries);
        const auto json = _getJson(zipEntries);

        herb.tr_name = _getTrName(json);
        herb.tr_content_path = _getTrContent(json);
        herb.name = _getName(json);





        return herb;
    }





private:
    libzippp::ZipArchive &_zip;

    std::string _getRootName(std::vector<libzippp::ZipEntry>& list){
        auto rootEntries = list.at(0);
        const auto name = rootEntries.getName();

        return name;
    }

    std::string _getJsonPath(std::vector<libzippp::ZipEntry>& list){


        for(const auto &file : list){
            if ( ! file.isFile() ){
                continue;
            }

            if( file.getName().find(".json") != std::string::npos ){
                return file.getName();
            }

        }


    }

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

    nlohmann::json _getJson(std::vector<libzippp::ZipEntry>& list){
        const auto jsonPath = _getJsonPath(list);
        auto zipEntries = _getZipEntry(jsonPath);
        const auto data = zipEntries.readAsText();


        return nlohmann::json::parse(data);
    }

    libzippp::ZipEntry &_getZipEntry(const std::string &path){

        for(auto &it : _zip.getEntries()){
            if( it.getName() == path)
                return it;
        }

    }


    std::map<std::string, std::string> _getTrName(const nlohmann::json &json){
    std::map<std::string, std::string> tr;

    for(const auto &it: json["tr_name"]){
            std::string lang = it["lang"];
            std::string name = it["name"];

            tr.insert({lang,name});
        }


    return tr;
    }

    std::map<std::string, std::string> _getTrContent(const nlohmann::json &json){
    std::map<std::string, std::string> tr;

    for(const auto &it: json["tr_content"]){
            std::string lang = it["lang"];
            std::string name = it["file"];

            tr.insert({lang,name});
        }


    return tr;
    }

    std::string _getName(const nlohmann::json &json){
        return   json["name"];
    }

};

std::string readFileZip(libzippp::ZipArchive &zip ,const std::string &path){

    for(auto &it : zip.getEntries()){
        if (  it.getName().find(path) != std::string::npos){
            return it.readAsText();
        }
    }

    throw std::runtime_error("no found");
}

void insertToSql(libzippp::ZipArchive &zip ,const Herb& herb){


    auto clientPtr = drogon::app().getDbClient();

    const auto readBody = readFileZip(zip, herb.tr_content_path.at("ru") );



    {
        auto result = clientPtr->execSqlSync(R"(INSERT INTO TrLang (TrLangId,Lang,Name) VALUES (0,'ru',$1);)", herb.tr_name.at("ru")  );

    }

    {
        auto result = clientPtr->execSqlSync(R"(INSERT INTO Content (ContentId,Lang,Path) VALUES (0,'ru',$1);)", readBody);

    }

    {
        auto result = clientPtr->execSqlSync(R"(INSERT INTO Herb (Name,Content,TrLang) VALUES ($1,0,0);)", herb.name  );

    }




}

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

    insertToSql(zf, herb);


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
