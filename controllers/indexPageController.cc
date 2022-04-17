#include "indexPageController.h"

void indexPageController::asyncHandleHttpRequest( [[maybe_unused]] const HttpRequestPtr& req, std::function<void (const HttpResponsePtr &)> &&callback)
{
    using namespace drogon;



    HttpViewData data;

    auto resp = HttpResponse::newHttpViewResponse("indexPage.csp", data);

    callback(resp);
}
