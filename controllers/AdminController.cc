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


    HttpViewData data;

    auto resp = HttpResponse::newHttpViewResponse("uploadPage.csp", data);

    callback(resp);


}

void AdminController::addHerb(const drogon::HttpRequestPtr &req, std::function<void (const drogon::HttpResponsePtr &)> &&callback){

    using namespace drogon;

    if( !isCorrectAddress(req)  ){

        auto resp = HttpResponse::newRedirectionResponse("404",HttpStatusCode::k404NotFound);
        return;
    }



    auto requestBody = req->getJsonObject();

    if (requestBody == nullptr) {
         Json::Value jsonBody;
        jsonBody["status"] = "error";
        jsonBody["message"] = "body is required";

        auto response = HttpResponse::newHttpJsonResponse(jsonBody);
        response->setStatusCode(HttpStatusCode::k400BadRequest);

        callback(response);
        return;
    }



    auto jsonDoc = *requestBody;

    const auto herb = jsonToHerb(jsonDoc);

    DBController::addHerb(herb);



    Json::Value resp;
    resp["status"] = "ok";





    auto response = HttpResponse::newHttpJsonResponse(resp);

    callback(response);






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


