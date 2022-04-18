#include "HerbController.h"

void HerbController::renderHerber( [[maybe_unused]]  const drogon::HttpRequestPtr &req, Callback callback, const std::string& herbName) {
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



void HerbController::render(const drogon::HttpRequestPtr &req, Callback callback){

    auto clientPtr = drogon::app().getDbClient();
    auto result = clientPtr->execSqlSync(R"(SELECT * FROM Herb;)");

    std::stringstream html;


    for ( const auto &row : result ) {

        const auto name = row.at("Name").as<std::string>();

        html << R"(<p><a href="/herb/)" <<  name << "\">" << name  << "</a></p>";

    }



    auto resp = drogon::HttpResponse::newHttpResponse();

    resp->setBody( html.str() );

    callback(resp);

}



std::optional<HerbController::Item> HerbController::getItem(const std::string &name){

    auto clientPtr = drogon::app().getDbClient();
    auto result = clientPtr->execSqlSync(R"(SELECT * FROM Herb WHERE Name = $1;)", name);

    if ( result.empty() ){
        return {};
    }


    Item item;
    item.name = result.at(0).at("Name").as<std::string>();
    item.htmlBody = result.at(0).at("HtmlBody").as<std::string>();



    return item;
}
