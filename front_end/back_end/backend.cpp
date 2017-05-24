/*-----------------------------------------------------
 File Name : backend.cpp
 Purpose :
 Creation Date : 22-05-2017
 Last Modified : Wed May 24 16:41:18 2017
 Created By : Jeasine Ma [jeasinema[at]gmail[dot]com]
-----------------------------------------------------*/
#include <string>
#include <vector>
#include <iostream>
#include <memory>

#include "sio_client.h"
#include "sio_socket.h"

#include "back_end/backend.h"
#include "db_parser/metadata.h"
#include "db_parser/movie_db.h"
#include "viewer/base_render.h"

namespace persudo {
namespace backend {

using db_parser::PersudoData;

int PersudoBackend::register_all() {
    int ret = 0;
    client.set_open_listener([&]() {
        sio::socket::ptr s = client.socket();

        s->on(this->index_site.get_recv_event_name(), sio::socket::event_listener_aux([s, this](string const& name, sio::message::ptr const& data,
                bool isAck, sio::message::list &ack_resp) {
            this->index_site.recv_server_data = data; // get it from server 
            sio::message::ptr p = sio::binary_message::create(this->index_site.get_website());
            s->emit(this->index_site.get_send_event_name(), p);
        }));

        s->on(this->search_site.get_recv_event_name(), sio::socket::event_listener_aux([s, this](string const& name, sio::message::ptr const& data,
                bool isAck, sio::message::list &ack_resp) {
            this->index_site.recv_server_data = data; // get it from server 
            sio::message::ptr p = sio::binary_message::create(this->search_site.get_website());
            s->emit(this->search_site.get_send_event_name(), p);
        }));

        s->on(this->movie_info_site.get_recv_event_name(), sio::socket::event_listener_aux([s, this](string const& name, sio::message::ptr const& data,
                bool isAck, sio::message::list &ack_resp) {
            this->index_site.recv_server_data = data; // get it from server 
            sio::message::ptr p = sio::binary_message::create(this->movie_info_site.get_website());
            s->emit(this->movie_info_site.get_send_event_name(), p);
        }));

        s->on(this->actor_info_site.get_recv_event_name(), sio::socket::event_listener_aux([s, this](string const& name, sio::message::ptr const& data,
                bool isAck, sio::message::list &ack_resp) {
            this->index_site.recv_server_data = data; // get it from server 
            sio::message::ptr p = sio::binary_message::create(this->actor_info_site.get_website());
            s->emit(this->actor_info_site.get_send_event_name(), p);
        }));

        s->on(this->relate_info_site.get_recv_event_name(), sio::socket::event_listener_aux([s, this](string const& name, sio::message::ptr const& data,
                bool isAck, sio::message::list &ack_resp) {
            this->index_site.recv_server_data = data; // get it from server 
            sio::message::ptr p = sio::binary_message::create(this->relate_info_site.get_website());
            s->emit(this->relate_info_site.get_send_event_name(), p);
        }));

    });
    return ret;
}

int PersudoBackend::start() {
    int ret = 0;
    if (this->register_all()) {
        std::cerr << "call back register failed!" << std::endl;
        ret = 1;
    } else {
        while (!this->client.opened())
            this->client.connect(this->master_uri);
        std::cerr << "client has been started" << std::endl;
        ret = 0;
    }
    return ret;
}

int PersudoBackend::stop(bool force) {
    if (force)
        this->client.close(); 
    else 
        this->client.sync_close();
    std::cerr << "client has been closed" << std::endl;
    return 0;
}

IndexSite::IndexSite() 
    : BaseSite()
{
    // create render and base site
    this->recv_event_name = "server_get_index";
    this->send_event_name = "cpp_send_index";
    this->db_name = "movie_db";
    this->render = std::make_shared<IndexRender>("../front_end/web_server/views/static/index.html");
    this->db = std::make_shared<MovieDB>(this->db_name);
}

shared_ptr<string> IndexSite::get_website() {
    string region = recv_server_data->get_map().at("region")->get_string();
    auto db = std::static_pointer_cast<MovieDB>(this->db);
    auto movies = db->get_movie_today(region);
    
    auto metadata = std::make_shared<PersudoData>();
    for (auto& i : movies) {
        auto movie = db->get_movie_data(i);
        metadata->movie_data.push_back(movie);
    }

    return this->render->render(metadata);
}

SearchSite::SearchSite() 
    : BaseSite()
{
    // create render and base site
    this->recv_event_name = "server_get_search";
    this->send_event_name = "cpp_send_search";
    this->db_name = "movie_db";
    this->render = std::make_shared<SearchRender>("../front_end/web_server/views/static/search.html");
    this->db = std::make_shared<MovieDB>(this->db_name);
}

shared_ptr<string> SearchSite::get_website() {
    string keyword = recv_server_data->get_map().at("keyword")->get_string();
    auto db = std::static_pointer_cast<MovieDB>(this->db);
    auto movies = db->search_movie(keyword);

    auto metadata = std::make_shared<PersudoData>();
    for (auto& i : movies) {
        auto movie = db->get_movie_data(i);
        metadata->movie_data.push_back(movie);
    }

    return this->render->render(metadata);
}

MovieInfoSite::MovieInfoSite() 
    : BaseSite()
{
    // create render and base site
    this->recv_event_name = "server_get_movieinfo";
    this->send_event_name = "cpp_send_movieinfo";
    this->db_name = "movie_db";
    this->render = std::make_shared<MovieInfoRender>("../front_end/web_server/views/static/detail.html");
    this->db = std::make_shared<MovieDB>(this->db_name);
}

shared_ptr<string> MovieInfoSite::get_website() {
    string movie_name = recv_server_data->get_map().at("movie")->get_string();
    auto db = std::static_pointer_cast<MovieDB>(this->db);
    auto movie = db->get_movie_data(movie_name);

    auto metadata = std::make_shared<PersudoData>();
    metadata->movie_data.push_back(movie);

    return this->render->render(metadata);
}

ActorInfoSite::ActorInfoSite() 
    : BaseSite()
{
    // create render and base site
    this->recv_event_name = "server_get_actorinfo";
    this->send_event_name = "cpp_send_actorinfo";
    this->db_name = "movie_db";
    this->render = std::make_shared<ActorInfoRender>("../front_end/web_server/views/static/detail.html");
    this->db = std::make_shared<MovieDB>(this->db_name);
}

shared_ptr<string> ActorInfoSite::get_website() {
    string movie_name = recv_server_data->get_map().at("movie")->get_string();
    auto db = std::static_pointer_cast<MovieDB>(this->db);
    auto movie = db->get_movie_data(movie_name);

    auto metadata = std::make_shared<PersudoData>();
    metadata->movie_data.push_back(movie);

    return this->render->render(metadata);
}

RelateInfoSite::RelateInfoSite() 
    : BaseSite()
{
    // create render and base site
    this->recv_event_name = "server_get_relateinfo";
    this->send_event_name = "cpp_send_relateinfo";
    this->db_name = "movie_db";
    this->render = std::make_shared<RelateInfoRender>("../front_end/web_server/views/static/detail.html");
    this->db = std::make_shared<MovieDB>(this->db_name);
}

shared_ptr<string> RelateInfoSite::get_website() {
    string movie_name = recv_server_data->get_map().at("movie")->get_string();
    auto db = std::static_pointer_cast<MovieDB>(this->db);
    auto movie = db->get_movie_data(movie_name);

    auto metadata = std::make_shared<PersudoData>();
    metadata->movie_data.push_back(movie);

    return this->render->render(metadata);
}

}
}
