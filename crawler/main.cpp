#include <cstdint>
#include <iostream>
#include <vector>
#include <bsoncxx/json.hpp>
#include <mongocxx/client.hpp>
#include <mongocxx/stdx.hpp>
#include <mongocxx/uri.hpp>
#include <mongocxx/client.hpp>
#include <mongocxx/instance.hpp>
#include "actor.hpp"
#include "CRAW.hpp"
#include "movie.hpp"
#include "daily_movie.hpp"
#include "database.h"
#include "url.hpp"
#include <fstream>

using bsoncxx::builder::stream::open_array;
using bsoncxx::builder::stream::close_array;
using bsoncxx::builder::stream::close_document;
using bsoncxx::builder::stream::document;
using bsoncxx::builder::stream::finalize;
using bsoncxx::builder::stream::open_array;
using bsoncxx::builder::stream::open_document;



/*
void today_movie()
{
    document builder{};

    builder << "region" << "us";

    auto in_array = builder << "movie_relate" << open_array;
    for (auto&& e : {1, 2, 3}) {
        in_array = in_array <<  e;
    }
    auto _builder = (in_array << close_array);

    _builder << "another_key" << 42;

    auto doc = _builder << finalize;

    //std::cout << bsoncxx::to_json(doc) << std::endl;

    collection2.insert_one(doc.view());

}
*/
int main(int, char**) {


    ifstream in("chinese");
    string str;
    database db;
    CRAW craw;
    Douban_m douban_data;
    Douban search;

    while (!in.eof())
    {
        cout << "haha" << endl;
        in >> str;
        search.get_url(str);
        cout << str;
        for(auto& x: search.url)
        {
            cout << x << endl;
            string aim =  craw.getPageContent(x);
            douban_data.get_data(aim);
            //douban_data.print_info();
            db.push_in(douban_data.movie, str);
        }
    }
    return 0;
}

