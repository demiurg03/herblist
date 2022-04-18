#include <drogon/drogon.h>


using Callback =  std::function<void(const drogon::HttpResponsePtr &)> &&;

class HerbController : public drogon::HttpController<HerbController>
{

    //FIXME: rename
    struct Item{

        std::string name;
        std::string htmlBody;

    };


public:

    PATH_LIST_BEGIN

    ADD_METHOD_TO(HerbController::renderHerber, "herb/{1}", drogon::Get );
    ADD_METHOD_TO(HerbController::render, "herb/", drogon::Get );
    PATH_LIST_END


    void render(const drogon::HttpRequestPtr &req, Callback callback);



    void renderHerber(const drogon::HttpRequestPtr &req,  std::function<void(const drogon::HttpResponsePtr &)> &&callback, const std::string& herbName);




    std::optional<Item> getItem(const std::string &name);


};


