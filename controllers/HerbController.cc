#include "HerbController.h"

void HerbController::render( [[maybe_unused]]  const drogon::HttpRequestPtr &req,
std::function<void (const drogon::HttpResponsePtr &)> &&callback,
const std::string& herbName)
{
    using namespace drogon;


    const auto item = getItem(herbName);

    if( !item.has_value() ){

        auto resp = HttpResponse::newRedirectionResponse("404",HttpStatusCode::k404NotFound);

        return;
    }

    const auto itemValue = item.value();

    HttpViewData data;


    data.insert("title", itemValue.name);
    data.insert("body", itemValue.htmlBody);

    auto resp = HttpResponse::newHttpViewResponse("herbPage.csp", data);



    callback(resp);

}
