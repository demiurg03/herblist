#pragma once

#include <drogon/drogon.h>

using namespace drogon;

class indexPageController : public drogon::HttpSimpleController<indexPageController>
{
  public:
    virtual void asyncHandleHttpRequest(const HttpRequestPtr& req, std::function<void (const HttpResponsePtr &)> &&callback) override;
    PATH_LIST_BEGIN
    // list path definitions here;
    PATH_ADD("/")
    PATH_LIST_END
};
