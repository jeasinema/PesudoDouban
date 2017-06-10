//
// Created by liyr on 2017/6/4.
//

#include "database.h"
mongocxx::instance database::inst{};
mongocxx::client database::conn{mongocxx::uri{}};


void database::push_in(MOVIE *movie, string str) {
    if(movie == 0) {
        cout << "failed" << endl;
        return;
    }
    auto collection1 = database::conn["moviedb"]["movie"];

    document builder{};


    builder << "movie_name" << str;
    builder << "movie_date" << string(movie->getDate()[0]);
    builder << "movie_time" << string(movie->getDuration());
    //builder << "movie_rate" << 123;
    //builder << "movie_level" << "pg-13";
    builder << "movie_poster_id" << string(movie->getPoster());
    //builder << "movie_name_id" << "string";
    auto in_array = builder << "movie_class" << open_array;
    for (auto&& e : movie->genre) {
        in_array = in_array <<  string(e);
    }
    auto _builder = (in_array << close_array);
    //_builder << "movie_abstract" << "string";
    //_builder << "movie_detail" << "string";

   //in_array = _builder << "movie_critic" << open_array;
   //for (auto&& e : {"user_name", "date", "detail"}) {
   //    in_array = in_array << open_document << "user_name" << "haha"
   //                        << "date" << "haha"
   //                        << "detail" << "guagua"
   //                        << close_document;
   //}
   //_builder = in_array << close_array;

    in_array = _builder << "movie_actor" << open_array;
    for (auto&& e : movie->getActor()) {
        in_array = in_array << open_document << "name" << string(e)
                            << "image_id" << -1
                            << close_document;
    }
    _builder = in_array << close_array;

    in_array = _builder << "movie_dirctor" << open_array;
    for (auto&& e : movie->getDirector()) {
        in_array = in_array << open_document << "name" << string(e)
                            << "image_id" << -1
                            << close_document;
    }
    _builder = in_array << close_array;

    in_array = _builder << "movie_writer" << open_array;
    for (auto&& e : movie->getWriter()) {
        in_array = in_array << open_document << "name" << string(e)
                            << "image_id" << -1
                            << close_document;
    }
    _builder = in_array << close_array;

    //in_array = _builder << "movie_relate" << open_array;
    //for (auto&& e : {1, 2, 3}) {
    //    in_array = in_array <<  e;
    //}
    //_builder = (in_array << close_array);

    auto doc = _builder << finalize;

    //std::cout << bsoncxx::to_json(doc) << std::endl;

    collection1.insert_one(doc.view());
    //auto collection2 = database::conn["moviedb"]["today_movie"];
    auto cursor = collection1.find({});
    for(auto doc : cursor) {
        std::cout << bsoncxx::to_json(doc) << "\n";
    }
}
/*
void database::push_in(MOVIE *movie)
{
    for (auto&& doc : cursor) {
        std::cout << bsoncxx::to_json(doc) << std::endl;
    }
}
*/