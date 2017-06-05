/*-----------------------------------------------------
 File Name : base_rander.cpp
 Purpose :
 Creation Date : 21-05-2017
 Last Modified : Mon May 29 14:36:26 2017
 Created By : Jeasine Ma [jeasinema[at]gmail[dot]com]
-----------------------------------------------------*/
#include <fstream>
#include <sstream>
#include <cassert>
#include <iostream>

#include "viewer/base_render.h"

namespace persudo {
namespace viewer {

using persudo::db_parser::PersudoData;
using persudo::db_parser::MovieData;
using persudo::db_parser::PersonData;
using persudo::db_parser::MovieCritic;

shared_ptr<string> BaseRender::render(shared_ptr<MetaData> _data_) {
    return this->base_template;
}

int BaseRender::load_template(const string& template_path) {
    this->base_template = std::make_shared<string>();
    std::ifstream f(template_path);
    if (f.is_open()) {
        std::stringstream ss;
        ss << f.rdbuf();
        *(this->base_template) = ss.str();
        std::cerr << "open template: " << template_path << " success!" << std::endl;
    } else {
        std::cerr << "open template: " << template_path << " failed!" << std::endl;
    }
    return 1;
}

shared_ptr<string> IndexRender::render(shared_ptr<MetaData> _data_) {
    auto data = std::static_pointer_cast<PersudoData>(_data_);
    bool no_movie = (data->movie_data.size() == 0);
    mstch::map context{
        { "no_movie", no_movie },
        { "china_movie_url", this->_url_.china_movie_url },
        { "us_movie_url", this->_url_.us_movie_url },
        { "japan_movie_url", this->_url_.japan_movie_url },
        { "movies", extract_movie_info(data) }
    };
    auto ret = std::make_shared<string>(mstch::render(*this->base_template, context));
    return ret;
}

shared_ptr<string> SearchRender::render(shared_ptr<MetaData> _data_) {
    auto data = std::static_pointer_cast<PersudoData>(_data_);
    int search_amount = data->movie_data.size();
    mstch::map context{
        { "search_amount", search_amount },
        { "search_results", extract_movie_info(data) }
    };
    auto ret = std::make_shared<string>(mstch::render(*this->base_template, context));
    return ret;
}

shared_ptr<string> MovieInfoRender::render(shared_ptr<MetaData> _data_) {
    auto data = std::static_pointer_cast<PersudoData>(_data_);
    if (data->movie_data.size() == 0) std::cerr << "movie_data size is 0!" << std::endl;
    mstch::map context{
        { "basic_info_url", build_url(this->_url_.basic_info_url,
                                      data->movie_data[0]->movie_name) },
        { "is_basic_info", true },
        { "actor_info_url", build_url(this->_url_.actor_info_url,
                                      data->movie_data[0]->movie_name) },
        { "is_actor_info", false },
        { "relate_info_url", build_url(this->_url_.relate_info_url,
                                       data->movie_data[0]->movie_name) },
        { "is_relate_info", false },
        { "movie_poster_url", build_url(this->_url_.movie_poster_url_prefix 
                ,data->movie_data[0]->movie_poster_id) },
        { "movie_name", data->movie_data[0]->movie_name },
        { "movie_rate", data->movie_data[0]->movie_rate },
        { "movie_level", data->movie_data[0]->movie_level },
        { "movie_time", data->movie_data[0]->movie_time },
        { "movie_classes", extract_movie_class(data->movie_data[0]) },
        { "movie_date", data->movie_data[0]->movie_date },
        { "movie_detail", *(data->movie_data[0]->movie_detail) },
        { "movie_critic", extract_movie_critic(data->movie_data[0]) }
    };
    auto ret = std::make_shared<string>(mstch::render(*this->base_template, context));

using db_parser::PersudoData;
    return ret;
}

shared_ptr<string> ActorInfoRender::render(shared_ptr<MetaData> _data_) {
    auto data = std::static_pointer_cast<PersudoData>(_data_);
    if (data->movie_data.size() == 0) std::cerr << "movie_data size is 0!" << std::endl;
    if (data->movie_data[0]->movie_director.size() == 0) std::cerr << "movie_director size is 0!" << std::endl;
    if (data->movie_data[0]->movie_writer.size() == 0) std::cerr << "movie_writer size is 0!" << std::endl;
    if (data->movie_data[0]->movie_star.size() == 0) std::cerr << "movie_star size is 0!" << std::endl;
    mstch::map context{
        { "basic_info_url", build_url(this->_url_.basic_info_url,
                                      data->movie_data[0]->movie_name) },
        { "is_basic_info", false },
        { "actor_info_url", build_url(this->_url_.actor_info_url,
                                      data->movie_data[0]->movie_name) },
        { "is_actor_info", true },
        { "relate_info_url", build_url(this->_url_.relate_info_url,
                                       data->movie_data[0]->movie_name) },
        { "is_relate_info", false },
        { "director_image_url", build_url(this->_url_.person_image_url_prefix,
                data->movie_data[0]->movie_director.size() == 0 ? "" : data->movie_data[0]->movie_director[0].image_id) },
        { "director_name", data->movie_data[0]->movie_director.size() == 0 ? "路人甲" : data->movie_data[0]->movie_director[0].name },
        { "writer_image_url", build_url(this->_url_.person_image_url_prefix,
                data->movie_data[0]->movie_writer.size() == 0 ? "" : data->movie_data[0]->movie_writer[0].image_id) },
        { "writer_name", data->movie_data[0]->movie_writer.size() == 0 ? "路人甲" : data->movie_data[0]->movie_writer[0].name },
        { "actors", extract_actor_info(data->movie_data[0]) }
    };    

    auto ret = std::make_shared<string>(mstch::render(*this->base_template, context));
    return ret;
}

shared_ptr<string> RelateInfoRender::render(shared_ptr<MetaData> _data_) {
    auto data = std::static_pointer_cast<PersudoData>(_data_);
    if (data->movie_data.size() == 0) std::cerr << "movie_data size is 0!" << std::endl;
    bool no_movie = (data->movie_data[0]->movie_relate.size() == 0);
    mstch::map context{
        { "basic_info_url", build_url(this->_url_.basic_info_url,
                                      data->movie_data[0]->movie_name) },
        { "is_basic_info", false },
        { "actor_info_url", build_url(this->_url_.actor_info_url,
                                      data->movie_data[0]->movie_name) },
        { "is_actor_info", false },
        { "relate_info_url", build_url(this->_url_.relate_info_url,
                                       data->movie_data[0]->movie_name) },
        { "is_relate_info", true },
        { "no_movie", no_movie },
        { "movies", extract_movie_info(data) }
    };
    auto ret = std::make_shared<string>(mstch::render(*this->base_template, context));
    return ret;
}

}
}
