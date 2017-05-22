/*-----------------------------------------------------
 File Name : main.cpp
 Purpose :
 Creation Date : 20-05-2017
 Last Modified : Sat May 20 21:30:12 2017
 Created By : Jeasine Ma [jeasinema[at]gmail[dot]com]
-----------------------------------------------------*/
#include <iostream>
#include <string>
#include <mstch/mstch.hpp>

#include "sio_client.h"
#include "sio_socket.h"

using namespace std;
using namespace sio;


int main(int argc, char **argv) {
    sio::client h;

    h.set_open_listener([&]() {
        sio::socket::ptr s = h.socket();
        
        sio::message::ptr p = sio::bool_message::create(true);
        s->emit("cpp_client", p);
        std::cout << "emit a cpp_client" << std::endl;

        s->on("server_get_page", sio::socket::event_listener_aux([s](string const& name, message::ptr const& data,
                        bool isAck,message::list &ack_resp) {
            string s1 = data->get_string();
            cout << "recv:" << s1 << endl;
            std::string view{"{{#names}}Hi {{name}}!\n{{/names}}"};
            mstch::map context{
                {"names",  mstch::array{
                    mstch::map{{"name", std::string{s1}}}
                }}
            };
            sio::message::ptr p = sio::string_message::create(string(mstch::render(view, context)));
            s->emit("cpp_push_page", p);
        }));
    });

    h.connect("http://127.0.0.1:8088");
    return 0;
}
