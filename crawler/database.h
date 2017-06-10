#ifndef OOPPRO_DATABASE_H
#define OOPPRO_DATABASE_H
#include <cstdint>
#include <iostream>
#include <vector>
#include <bsoncxx/json.hpp>
#include <mongocxx/client.hpp>
#include <mongocxx/stdx.hpp>
#include <mongocxx/uri.hpp>
#include <mongocxx/client.hpp>
#include <mongocxx/instance.hpp>
#include "movie.hpp"
using bsoncxx::builder::stream::open_array;
using bsoncxx::builder::stream::close_array;
using bsoncxx::builder::stream::close_document;
using bsoncxx::builder::stream::document;
using bsoncxx::builder::stream::finalize;
using bsoncxx::builder::stream::open_array;
using bsoncxx::builder::stream::open_document;


class database {
    static mongocxx::instance inst;
    static mongocxx::client conn;
public:
    void push_in(MOVIE *movie, string str);
};


#endif //OOPPRO_DATABASE_H
