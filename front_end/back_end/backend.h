/*-----------------------------------------------------
 File Name : backend.h
 Purpose :
 Creation Date : 22-05-2017
 Last Modified : Mon May 22 16:17:31 2017
 Created By : Jeasine Ma [jeasinema[at]gmail[dot]com]
-----------------------------------------------------*/
#ifndef BACKEND_H
#define BACKEND_H 

#include <string>
#include <vector>
#include <iostream>
#include <memory>

#include "sio_client.h"
#include "sio_socket.h"

#include "db_parser/metadata.h"
#include "db_parser/movie_db.h"
#include "viewer/base_render.h"

namespace persudo {
namespace backend {

using std::string;
using std::vector;
using std::cerr;
using std::endl;
using std::shared_ptr;

using db_parser::BaseDB;
using db_parser::MovieDB;
using viewer::BaseRender;
using viewer::IndexRender;
using viewer::SearchRender;
using viewer::MovieInfoRender;
using viewer::ActorInfoRender;
using viewer::RelateInfoRender;

class BaseSite {
protected:
    // node will use this event to get the static site
    string recv_event_name;
    string send_event_name;
    string db_name;
    shared_ptr<BaseDB> db;
    shared_ptr<BaseRender> render;
public:
    BaseSite() = default;
    BaseSite(shared_ptr<BaseDB> db, shared_ptr<BaseRender> render)
        : db(db), render(render) {}
    ~BaseSite() = default;

    string get_recv_event_name() { return recv_event_name; }
    string get_send_event_name() { return send_event_name; }
    // for this stupid demand. just return the whole static site
    virtual shared_ptr<string> get_website() = 0;
};

class IndexSite : public BaseSite  {
public:
    IndexSite();
    ~IndexSite() = default;
    shared_ptr<string> get_website();
};

class SearchSite : public BaseSite  {
public:
    SearchSite();
    ~SearchSite() = default;
    shared_ptr<string> get_website();
};

class MovieInfoSite : public BaseSite  {
public:
    MovieInfoSite();
    ~MovieInfoSite() = default;
    shared_ptr<string> get_website();
};

class ActorInfoSite : public BaseSite  {
public:
    ActorInfoSite();
    ~ActorInfoSite() = default;
    shared_ptr<string> get_website();
};

class RelateInfoSite : public BaseSite  {
public:
    RelateInfoSite();
    ~RelateInfoSite() = default;
    shared_ptr<string> get_website();
};

class PersudoBackend {
    string master_uri = "http://127.0.0.1:8088"; 
    sio::client client;

    int register_all();  // register all callback

    // sites 
    IndexSite index_site;
    SearchSite search_site;
    MovieInfoSite movie_info_site;
    ActorInfoSite actor_info_site;
    RelateInfoSite relate_info_site;
    
public:
    PersudoBackend() = default;
    PersudoBackend(const string& uri)
        : master_uri(uri) {}
    PersudoBackend(const PersudoBackend&) = default;
    ~PersudoBackend() = default;
    
    int start();
    int stop(bool force = false);
};


}
}

#endif /* BACKEND_H */
