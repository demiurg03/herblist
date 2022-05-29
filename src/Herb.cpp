#include "Herb.hpp"





Herb jsonToHerb(const Json::Value &value){

    Herb herb;


    if (  value.isMember("id") ){

        auto idJson = value.get("id", "-" );

        if( idJson.isUInt64() ){
            herb.id = idJson.asUInt64();
        }


    }


    herb.name = value["herbHame"].asString();
    herb.model = value["herbModel"].asString();
    herb.content = value["herbContent"].asString();





    return herb;
}
