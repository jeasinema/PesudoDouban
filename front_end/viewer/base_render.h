/*-----------------------------------------------------
 File Name :
 Purpose :
 Creation Date : 21-05-2017
 Last Modified : Mon May 29 13:55:58 2017
 Created By : Jeasine Ma [jeasinema[at]gmail[dot]com]
-----------------------------------------------------*/
#ifndef BASE_RENDER_H
#define BASE_RENDER_H 

#include <string>
#include <vector>
#include <map>
#include <memory>
#include <iostream>

#include <mstch/mstch.hpp>

#include "db_parser/metadata.h"

namespace persudo {
namespace viewer {

using std::vector;
using std::string;
using std::map;
using std::shared_ptr;
using std::weak_ptr;
using persudo::db_parser::MetaData;
using persudo::db_parser::MovieData;
using persudo::db_parser::PersudoData;

struct Url {
    // static
    string china_movie_url = "/index/china";
    string us_movie_url = "/index/us";
    string japan_movie_url = "/index/japan";
    string basic_info_url = "http://127.0.0.1:3000/detail/movieinfo/";
    string actor_info_url = "http://127.0.0.1:3000/detail/actorinfo/";
    string relate_info_url = "http://127.0.0.1:3000/detail/relateinfo/";

    // preifix
    // string movie_poster_url_prefix = "http://127.0.0.1/poster/";
    // string movie_name_url_prefix = "http://127.0.0.1/detail/";
    // string person_image_url_prefix = "http://127.0.0.1/image/";
    string movie_poster_url_prefix = "";
    string movie_name_url_prefix = "http://127.0.0.1:3000/detail/movieinfo/";
    string person_image_url_prefix = "";
};

class BaseRender {
protected:
    shared_ptr<string> base_template;
public:
    BaseRender() = default;
    ~BaseRender() = default;

    virtual shared_ptr<string> render(shared_ptr<MetaData> _data_);
    virtual int load_template(const string& template_path);

    // utils
    inline string build_url(const string& prefix, const string& id) {
        return prefix + id;
    }

};

class PersudoRender : public BaseRender {
protected:
    Url _url_;

    // limits
    int max_actor = 3;
    int max_class = 3;

    // utils
    mstch::array extract_actor_info(shared_ptr<MovieData> data); 
    mstch::array extract_movie_class(shared_ptr<MovieData> data); 
    mstch::array extract_movie_critic(shared_ptr<MovieData> data); 
    mstch::array extract_movie_star_name(shared_ptr<MovieData> data); 
    mstch::array extract_movie_info(shared_ptr<PersudoData> data); 
};


class IndexRender : public PersudoRender {
public:
    IndexRender(const string& template_path) { load_template(template_path); }
    shared_ptr<string> render(shared_ptr<MetaData> _data_);
};

class SearchRender : public PersudoRender {
public:
    SearchRender(const string& template_path) { load_template(template_path); }
    shared_ptr<string> render(shared_ptr<MetaData> _data_);
};

class MovieInfoRender : public PersudoRender {
public:
    MovieInfoRender(const string& template_path) { load_template(template_path); }
    shared_ptr<string> render(shared_ptr<MetaData> _data_);
};

class ActorInfoRender : public PersudoRender {
public:
    ActorInfoRender(const string& template_path) { load_template(template_path); }
    shared_ptr<string> render(shared_ptr<MetaData> _data_);
};

class RelateInfoRender : public PersudoRender {
public:
    RelateInfoRender(const string& template_path) { load_template(template_path); }
    shared_ptr<string> render(shared_ptr<MetaData> _data_);
};

inline mstch::array PersudoRender::extract_movie_star_name(shared_ptr<MovieData> data) {
    mstch::array ret;
    for (auto& i : data->movie_star) {
        mstch::map element{
            { "movie_star_name", i.name }
        };
        ret.push_back(element);
    }
    if (ret.size() > this->max_actor) {
        ret.resize(this->max_actor);
    }
    return ret;
}

inline mstch::array PersudoRender::extract_movie_class(shared_ptr<MovieData> data) {
    mstch::array ret;
    for (auto& i : data->movie_class) {
        mstch::map element{
            { "movie_class", i }
        };
        ret.push_back(element);
    }
    if (ret.size() > this->max_class) {
        ret.resize(this->max_class);
    }
    return ret;
}

inline mstch::array PersudoRender::extract_movie_critic(shared_ptr<MovieData> data) {
    mstch::array ret;
    for (auto& i : data->movie_critic) {
        mstch::map element{
            { "critic_user_name", i.user_name },
            { "critic_date", i.date },
            { "critic_detail", i.detail }
        };
        ret.push_back(element);
    }
    return ret;
}

inline mstch::array PersudoRender::extract_actor_info(shared_ptr<MovieData> data) {
    mstch::array ret;
    for (auto& i : data->movie_star) {
        mstch::map element{
            { "actor_image_url", build_url(this->_url_.person_image_url_prefix 
                    ,i.image_id) },
            { "actor_name", i.name }
        };
        ret.push_back(element);
    }
    return ret;
}

inline mstch::array PersudoRender::extract_movie_info(shared_ptr<PersudoData> data) {
    mstch::array ret;
    if (data->movie_data.size() != 0) {  // empty list == false
        for (auto& i : data->movie_data) {
            std::cout << "now deal with " << i->movie_name << std::endl;
            mstch::map element{
                { "movie_poster_url", build_url(this->_url_.movie_poster_url_prefix 
                        ,i->movie_poster_id) },
                { "movie_name", i->movie_name },
                { "movie_name_url", build_url(this->_url_.movie_name_url_prefix 
                        ,i->movie_name) },  // TODO: just use movie name
                { "movie_date", i->movie_date },
                { "movie_time", i->movie_time },
                { "movie_rate", i->movie_rate },
                { "movie_stars", extract_movie_star_name(i) },
                { "movie_classes", extract_movie_class(i) },
                { "movie_abstract", i->movie_abstract == nullptr ? "" : *(i->movie_abstract) }
            };
            ret.push_back(element);
        }
    }
    return ret;
}


}
}

#endif /* BASE_RENDER_H */
