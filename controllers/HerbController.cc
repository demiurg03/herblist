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

    throw  NotImplemented("HerbController::render");


}



