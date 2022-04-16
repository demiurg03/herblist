/*
MIT License

Copyright (c) 2022 Maxim Palshin

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

#include <drogon/drogon.h>

#include <filesystem>
#include <iostream>
#include <chrono>


#include "views/generate/herbPage.h"
#include "views/generate/indexPage.h"


using Callback = std::function<void(const drogon::HttpResponsePtr &)> ;

std::size_t getThreadNum(){

    const auto hardware_concurrency = std::thread::hardware_concurrency();

    if( hardware_concurrency == 0)
        return 1;

    return hardware_concurrency;
}

std::string readFileAll(const std::string &path){

    std::FILE* file = std::fopen(path.c_str(), "r");

    try {

        std::string fileData;


        std::array<char, 512> buffer;

        long rb = 0;

        while ( (rb = std::fread(buffer.data(), sizeof (char), buffer.size(), file )) > 0) {

            fileData.insert( fileData.end(), buffer.begin(), buffer.begin() + rb );

        }



        std::fclose(file);



        return fileData;

    }  catch (...) /* FIXME:fix */ {

        std::fclose(file);
        throw;
    }



}


void g_update();

class DataBase{
public:

    DataBase(const std::string &path) : m_path( path ){




    }


    void start(){

        using namespace std::chrono_literals;

        auto loop = drogon::app().getLoop();

        g_update();

        loop->runEvery( 360min, g_update);



    }


    void update(){



        LOG_INFO << "Database upadte";

        namespace fs = std::filesystem;

        fs::directory_entry parsDir( m_path );

        for( const auto &dir : fs::directory_iterator( parsDir ) ){
            const auto pathString = dir.path().string();
            const auto bodyHtml = readFileAll( pathString+"/body.html" );

            ///std::cout << dir.path().filename() << '\n';


            map[dir.path().filename().string()] = bodyHtml;

        }

    }


    std::string getHerbBody(const std::string &name)const{
        return map.at(name);
    }

private:
    std::string m_path;
    std::map<std::string, std::string> map;



}*g_dataBase = nullptr;

void g_update(){
    g_dataBase->update();
}


void indexPageHandler([[maybe_unused]] const drogon::HttpRequestPtr &request, Callback &&callback) {
    using namespace drogon;



    HttpViewData data;
    data.insert("title", "");

    auto resp = HttpResponse::newHttpViewResponse("indexPage.csp", data);

    callback(resp);

}





class HerbController:public drogon::HttpController<HerbController>
{
public:

    PATH_LIST_BEGIN
    //METHOD_ADD(HerbController::login,"hello/{1}",false,drogon::Get);
    ADD_METHOD_TO(HerbController::login,"herb/{1}", drogon::Get);
    PATH_LIST_END


    void login(const drogon::HttpRequestPtr &req,  std::function<void(const drogon::HttpResponsePtr &)> &&callback, std::string str){
        using namespace drogon;



        const auto body = g_dataBase->getHerbBody(str);

        HttpViewData data;
        data.insert("title", str);
        data.insert("body",body);

        auto resp = HttpResponse::newHttpViewResponse("herbPage.csp", data);



        callback(resp);

    }

};



int main() {

    std::setlocale(LC_ALL, "");

    const auto threadNum = getThreadNum();


    drogon::app().addListener( "0.0.0.0", 8080 ).setThreadNum( threadNum );

    drogon::app().registerHandler("/", &indexPageHandler, {drogon::Get});

    drogon::app().enableGzip( true );

    drogon::app().setStaticFileHeaders( { {"font","font"}, {"herb", "herb"}}  );


    g_dataBase = new DataBase("herb");

    g_dataBase->start();
    drogon::app().run();



    return EXIT_SUCCESS;
}
