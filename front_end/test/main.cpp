/*-----------------------------------------------------
 File Name : main.cpp
 Purpose :
 Creation Date : 28-05-2017
 Last Modified : Mon May 29 11:24:09 2017
 Created By : Jeasine Ma [jeasinema[at]gmail[dot]com]
-----------------------------------------------------*/
#include <iostream>
#include <string>
#include <vector>
#include <memory>

#include "back_end/backend.h"

#include "sio_client.h"
#include "sio_socket.h"

using namespace std;
using namespace sio;

int main(int argc, char **argv) {
    std::cout << "starting backend!" << std::endl;
    auto backend = std::make_shared<persudo::backend::PersudoBackend>("http://127.0.0.1:3000");

    if (backend->start()) {
        std::cerr << "backend start failed!" << std::endl;
    } else {
        std::cout << "backend start successfully!" << std::endl;
    }
    std::cout << "Now handoff to waiting for connection..." << std::endl;
    backend->handoff();

    //sio::client client;
    //client.set_open_listener([&]() {        
    //    std::cout << "recv connection!" << std::endl;
    //    sio::socket::ptr s = client.socket();

    //    // response to node server    
    //    s->emit("cpp_client");
    //    s->on("server_get_index", sio::socket::event_listener_aux([s](string const& name, sio::message::ptr const& data,
    //        bool isAck, sio::message::list &ack_resp) {
    //        string region = data->get_map().at("region")->get_string();
    //        std::cout << "get index site " << region << std::endl;
    //    }));

    //});
    //client.connect("http://127.0.0.1:3000");
    while(1);
    return 0;
}
