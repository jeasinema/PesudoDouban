/*-----------------------------------------------------
 File Name :
 Purpose :
 Creation Date : 22-05-2017
 Last Modified : Sun May 28 19:57:48 2017
 Created By : Jeasine Ma [jeasinema[at]gmail[dot]com]
-----------------------------------------------------*/
#include "rapidjson/document.h"

#include "db_parser/movie_db.h"
#include "db_parser/metadata.h"

namespace persudo {
namespace db_parser {

shared_ptr<mongocxx::instance> DBConn::db_instance = nullptr;
unordered_map<string, shared_ptr<mongocxx::client>> DBConn::connected_cli = {{"", nullptr}};

shared_ptr<MovieData> MovieDB::get_movie_data(const string& movie_name, bool with_relate) {
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
        rapidjson::Document docs;
        docs.Parse(bsoncxx::to_json(viewer).c_str());
        ret->movie_name = (docs)["movie_name"].GetString();
        ret->movie_date = (docs)["movie_date"].GetString();
        ret->movie_time = (docs)["movie_time"].GetString();
        ret->movie_rate = (docs)["movie_rate"].GetInt();
        ret->movie_level = (docs)["movie_levle"].GetString();
        ret->movie_poster_id = (docs)["movie_poster_id"].GetString();
        ret->movie_name_id = (docs)["movie_name_id"].GetString();
        ret->movie_abstract = std::make_shared<string>((docs)["movie_abstract"].GetString());
        ret->movie_detail = std::make_shared<string>((docs)["movie_detail"].GetString());
        // build movie class
        for (auto& i : (docs)["movie_class"].GetArray()) {
            tmp.push_back(i.GetString());
        }
        ret->movie_class = tmp;
        tmp.clear();
        // build movie critic
        for (auto& i : (docs)["movie_critic"].GetArray()) {
            MovieCritic critic;
            critic.user_name = i["user_name"].GetString();
            critic.date = i["date"].GetString();
            critic.detail = i["detail"].GetString();
            tmp_critic.push_back(critic);
        }
        ret->movie_critic = tmp_critic;
        tmp_critic.clear();
        // build director
        for (auto& i : (docs)["movie_director"].GetArray()) {
            PersonData person;
            person.name = i["name"].GetString();
            person.image_id = i["image_id"].GetString();
            tmp_person.push_back(person);
        }
        ret->movie_star = tmp_person;
        tmp_person.clear();
        // build writer
        for (auto& i : (docs)["movie_writer"].GetArray()) {
            PersonData person;
            person.name = i["name"].GetString();
            person.image_id = i["image_id"].GetString();
            tmp_person.push_back(person);
        }
        ret->movie_writer = tmp_person;
        tmp_person.clear();
        // build star
        for (auto& i : (docs)["movie_actor"].GetArray()) {
            PersonData person;
            person.name = i["name"].GetString();
            person.image_id = i["image_id"].GetString();
            tmp_person.push_back(person);
        }
        ret->movie_star = tmp_person;
        tmp_person.clear();

        // build_relate_movie
        if (with_relate) {
            // get relate movie name
            for (auto& i : (docs)["movie_relate"].GetArray()) {
                tmp.push_back(i.GetString());
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
    mongocxx::collection coll = (this->db)[today_movie_coll_name];
    vector<string> ret;

    // fetch today movie by speicfiled region
    mongocxx::stdx::optional<bsoncxx::document::value> result =
      coll.find_one(document{} << "region" << region << finalize);
    bsoncxx::document::view viewer = result->view();
    rapidjson::Document docs;
    docs.Parse(bsoncxx::to_json(viewer).c_str());
    if (result) {
        for (auto& i : (docs)["movie"].GetArray()) {
            ret.push_back(i.GetString());
        }
    }
    return ret;
}

vector<string> MovieDB::search_movie(const string& movie_name) {
    // unimplemented
    return vector<string>{""};
}

}
}
