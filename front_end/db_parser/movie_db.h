/*-----------------------------------------------------
 File Name : movie_db.h
 Purpose :
 Creation Date : 22-05-2017
 Last Modified : Mon May 22 16:56:53 2017
 Created By : Jeasine Ma [jeasinema[at]gmail[dot]com]
-----------------------------------------------------*/
#ifndef MOVIE_DB_H
#define MOVIE_DB_H 

#include <string>
#include <vector>
#include <memory>
#include <unordered_map>

#include <mongocxx/client.hpp>
#include <mongocxx/instance.hpp>
#include <bsoncxx/builder/stream/document.hpp>
#include <bsoncxx/json.hpp>

#include "db_parser/metadata.h"

namespace persudo {
namespace db_parser {

using std::string;
using std::vector;
using std::shared_ptr;
using std::unordered_map;

using bsoncxx::builder::stream::close_array;
using bsoncxx::builder::stream::close_document;
using bsoncxx::builder::stream::document;
using bsoncxx::builder::stream::finalize;
using bsoncxx::builder::stream::open_array;
using bsoncxx::builder::stream::open_document;

class DBConn {
    static shared_ptr<mongocxx::instance> db_instance;
    static unordered_map<string, shared_ptr<mongocxx::client>> connected_cli;
    
    DBConn() = default;
public:
    inline static shared_ptr<mongocxx::client> get_client(const string& db_uri) {
        shared_ptr<mongocxx::client> ret;
        if (db_instance == nullptr) {
            db_instance = shared_ptr<mongocxx::instance>(new mongocxx::instance());
        }
        auto res = connected_cli.find(db_uri);
        if (res != connected_cli.end()) {
            ret = res->second;
        } else {
            mongocxx::uri uri(db_uri);
            ret = shared_ptr<mongocxx::client>(new mongocxx::client(uri));
            connected_cli[db_uri] = ret;
        }
        return ret;
    }

    DBConn(const DBConn&) = delete;
    DBConn& operator=(const DBConn&) = delete;
};

class BaseDB {
protected:
    shared_ptr<mongocxx::client> client;
    mongocxx::database db;
    const string mongo_uri = "mongodb://localhost:27017";    
    string db_name = "movie_db";   
public:
    BaseDB() {
        client = DBConn::get_client(mongo_uri);
        db = (*client)[db_name];
    }
    
    BaseDB(const string& db_name) {
        client = DBConn::get_client(mongo_uri);
        this->db_name = db_name;
        this->db = (*client)[db_name];   
    }

    ~BaseDB() = default;
}; 

class MovieDB : public BaseDB {
public:
    MovieDB() = default;
    MovieDB(const string& db_name)
        : BaseDB(db_name) {}

    // ret value do not extract relate movie infos
    shared_ptr<MovieData> get_movie_data(const string& movie_name);
    vector<string> get_movie_today(const string& region);
    vector<string> search_movie(const string& movie_name);
};

}
}

#endif /* MOVIE_DB_H */
