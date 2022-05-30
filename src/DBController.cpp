/**
 *
 *  @file DBController.cpp
 *  @author Maxim Palshin
 *
 *  Copyright 2022, Maxim Palshin.  All rights reserved.
 *  Use of this source code is governed by a MIT license
 *  that can be found in the License file.
 *
 *  herblist
 *
 */


#include "DBController.hpp"

void DBController::initDB(){

    Instance()._initDb();

}

void DBController::addHerb(const Herb herb){


    Instance()._addHerb(herb);





}

std::optional<Herb> DBController::getHerbByModel(const std::string &model){
    return Instance()._getHerbByModel( model );
}

std::vector<Herb> DBController::getAllHerb(){
    return Instance()._getAllHerb();
}

DBController &DBController::Instance()
{
    static DBController theSingleInstance;
    return theSingleInstance;
}

DBController::DBController()
{

}

void DBController::_initDb(){


    auto client = drogon::app().getDbClient();


    const auto result = client->execSqlSync("SELECT name FROM sqlite_schema");

    std::vector<std::string>tables;

    for(const auto &row : result){
        tables.push_back( row.at("name").as<std::string>() );
    }


    if( std::find( tables.begin(), tables.end(), "Herb") == tables.end() ){
        client->execSqlSync(R"(CREATE TABLE "Herb" ( "Id" INTEGER NOT NULL UNIQUE, "Model" TEXT UNIQUE, "Name" TEXT, "Content"	TEXT, PRIMARY KEY("Id" AUTOINCREMENT) ))");
    }

}

void DBController::_addHerb(const Herb herb){


    auto client = drogon::app().getDbClient();


    client->execSqlSync(R"(INSERT INTO Herb(Model,Name,Content) VALUES($1,$2,$3))", herb.model,herb.name,herb.content);

}

std::optional<Herb> DBController::_getHerbByModel(const std::string &model){

    auto client = drogon::app().getDbClient();

    auto result = client->execSqlSync(R"(SELECT * FROM Herb WHERE Model = $1;)", model);

    if ( result.empty() ){
        return std::nullopt;
    }


    Herb herb;
    herb.id = result.at(0).at("id").as<std::size_t>();
    herb.model = result.at(0).at("Model").as<std::string>();
    herb.name = result.at(0).at("Name").as<std::string>();
    herb.content = result.at(0).at("Content").as<std::string>();

    return herb;
}

std::vector<Herb> DBController::_getAllHerb(){



    auto client = drogon::app().getDbClient();
    auto result = client->execSqlSync(R"(SELECT * FROM Herb;)");


    std::vector<Herb> herbs;

    for ( const auto &row : result ) {

        Herb herb;
        herb.id = row.at("id").as<std::size_t>();
        herb.model = row.at("Model").as<std::string>();
        herb.name = row.at("Name").as<std::string>();
        herb.content =row.at("Content").as<std::string>();

        herbs.push_back( herb );

    }


    return herbs;
}
