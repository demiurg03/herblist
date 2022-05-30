/**
 *
 *  @file indexPageController.cpp
 *  @author Maxim Palshin
 *
 *  Copyright 2022, Maxim Palshin.  All rights reserved.
 *  Use of this source code is governed by a MIT license
 *  that can be found in the License file.
 *
 *  herblist
 *
 */


#include "indexPageController.h"

void indexPageController::asyncHandleHttpRequest( [[maybe_unused]] const HttpRequestPtr& req, std::function<void (const HttpResponsePtr &)> &&callback)
{
    using namespace drogon;

    HttpViewData data;

    auto resp = HttpResponse::newHttpViewResponse("indexPage.csp", data);

    callback(resp);
}
