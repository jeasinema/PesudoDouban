/*-----------------------------------------------------
 File Name :
 Purpose :
 Creation Date : 22-05-2017
 Last Modified : Wed May 31 22:07:13 2017
 Created By : Jeasine Ma [jeasinema[at]gmail[dot]com]
-----------------------------------------------------*/
#include <sstream>
#include <iostream>
#include <third_party/jsoncpp/dist/json/json.h>

#include "json/json.h"

#include "db_parser/movie_db.h"
#include "db_parser/metadata.h"

namespace persudo {
namespace db_parser {

shared_ptr<mongocxx::instance> DBConn::db_instance = nullptr;
unordered_map<string, shared_ptr<mongocxx::client>> DBConn::connected_cli = {{"", nullptr}};

shared_ptr<MovieData> MovieDB::get_movie_data(const string& movie_name, bool with_relate) {
    std::cout << "call get_movie_data" << std::endl;
    mongocxx::collection coll = (this->db)[movie_coll_name];
    auto ret = std::make_shared<MovieData>();
    vector<string> tmp;
    vector<MovieCritic> tmp_critic;
    vector<PersonData> tmp_person;

    // fetch and build the MovieData
    mongocxx::stdx::optional<bsoncxx::document::value> result =
      coll.find_one(document{} << "movie_name" << movie_name << finalize);
    if (result) {
        bsoncxx::document::view viewer = result->view();
        Json::Value docs;
        std::stringstream ss;
        ss << bsoncxx::to_json(viewer);
        ss >> docs;
        
        ret->movie_name = (docs).get("movie_name", "x-men").asString();
        ret->movie_date = (docs).get("movie_date", "20160701").asString();
        ret->movie_time = (docs).get("movie_time", "120min").asString();
        ret->movie_rate = (docs).get("movie_rate", 5).asInt();
        ret->movie_level = (docs).get("movie_level", "PG-13").asString();
        ret->movie_poster_id = (docs).get("movie_poster_id", "1").asString();
        ret->movie_name_id = (docs).get("movie_name_id", "1").asString();
        ret->movie_abstract = std::make_shared<string>((docs).get("movie_abstract", "...").asString());
        ret->movie_detail = std::make_shared<string>((docs).get("movie_detail", "......").asString());
        // build movie class
        auto list = (docs)["movie_class"];
        for (int i = 0; i < list.size(); ++i) {
            tmp.push_back(list[i].asString());
        }
        ret->movie_class = tmp;
        tmp.clear();
        // build movie critic
        list = (docs)["movie_critic"];
        for (int i = 0; i < list.size(); ++i) {
            MovieCritic critic;
            critic.user_name = list[i].get("user_name", "jeasinema").asString();
            critic.date = list[i].get("date", "20160701").asString();
            critic.detail = list[i].get("detail", "...").asString();
            tmp_critic.push_back(critic);
        }
        ret->movie_critic = tmp_critic;
        tmp_critic.clear();
        // build director
        list = (docs)["movie_director"];
        for (int i = 0; i < list.size(); ++i) {
            PersonData person;
            person.name = list[i].get("name", "James Cameron").asString();
            person.image_id = list[i].get("image_id", "1").asString();
            tmp_person.push_back(person);
        }
        ret->movie_director = tmp_person;
        tmp_person.clear();
        // build writer
        list = (docs)["movie_writer"];
        for (int i = 0; i < list.size(); ++i) {
            PersonData person;
            person.name = list[i].get("name", "James Cameron").asString();
            person.image_id = list[i].get("image_id", "1").asString();
            tmp_person.push_back(person);
        }
        ret->movie_writer = tmp_person;
        tmp_person.clear();
        // build star
        list = (docs)["movie_actor"];
        for (int i = 0; i < list.size(); ++i) {
            PersonData person;
            person.name = list[i].get("name", "Tom Hanks").asString();
            person.image_id = list[i].get("image_id", "1").asString();
            tmp_person.push_back(person);
        }
        ret->movie_star = tmp_person;
        tmp_person.clear();

        // build_relate_movie
        if (with_relate) {
            // get relate movie name
            list = (docs)["movie_relate"];
            for (int i = 0; i < list.size(); ++i) {
                tmp.push_back(list[i].asString());
            }
            // get relate info
            vector<shared_ptr<MovieData>> relate;
            for (auto& i : tmp) {
                relate.push_back(get_movie_data(i, false));
            }
            ret->movie_relate = relate;
            tmp.clear();
        }
    }
    return ret;
}

vector<string> MovieDB::get_movie_today(const string& region) {
    std::cout << "call get_movie_today" << std::endl;
    mongocxx::collection coll = (this->db)[today_movie_coll_name];
    vector<string> ret;

    std::cout << "fuck1" << std::endl;
    // fetch today movie by speicfiled region
    mongocxx::stdx::optional<bsoncxx::document::value> result =
      coll.find_one(document{} << "region" << region << finalize);
    bsoncxx::document::view viewer = result->view();
    Json::Value docs;
    std::stringstream ss;
    string s = bsoncxx::to_json(viewer);
    ss << s;
    ss >> docs;
    std::cout << "fuck2" << std::endl;
    if (result) {
    std::cout << "fuck3" << std::endl;
        auto list = (docs)["movie"];
    std::cout << "fuck4" << std::endl;
        for (int i = 0; i < list.size(); ++i) {
            ret.push_back(list[i].asString());
        }
    }
    std::cout << "fuck4" << std::endl;
    return ret;
}

vector<string> MovieDB::search_movie(const string& movie_name) {
    // unimplemented
    return vector<string>{""};
}

}
}
