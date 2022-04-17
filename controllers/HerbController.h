#include <drogon/drogon.h>

class HerbController : public drogon::HttpController<HerbController>
{

    //FIXME: rename
    struct Item{

        std::string name;
        std::string htmlBody;

    };


public:

    PATH_LIST_BEGIN

    ADD_METHOD_TO(HerbController::render,"herb/{1}", drogon::Get);
    PATH_LIST_END


    void render(const drogon::HttpRequestPtr &req,  std::function<void(const drogon::HttpResponsePtr &)> &&callback, const std::string& herbName);


    std::optional<Item> getItem(const std::string &name){

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


};


