/*-----------------------------------------------------
 File Name : main.cpp
 Purpose :
 Creation Date : 20-05-2017
 Last Modified : Sun May 28 16:49:25 2017
 Created By : Jeasine Ma [jeasinema[at]gmail[dot]com]
-----------------------------------------------------*/
#include <iostream>
#include <string>
#include <mstch/mstch.hpp>

#include "sio_client.h"
#include "sio_socket.h"

using namespace std;
using namespace sio;

#include <cstdlib>

#include <bsoncxx/builder/stream/array.hpp>
#include <bsoncxx/builder/stream/document.hpp>
#include <bsoncxx/builder/stream/helpers.hpp>
#include <bsoncxx/config/prelude.hpp>
#include <bsoncxx/types.hpp>


#include <bsoncxx/array/view.hpp>
#include <bsoncxx/array/view.hpp>
#include <bsoncxx/builder/basic/array.hpp>
#include <bsoncxx/builder/basic/document.hpp>
#include <bsoncxx/builder/basic/kvp.hpp>
#include <bsoncxx/document/value.hpp>
#include <bsoncxx/document/view.hpp>
#include <bsoncxx/json.hpp>
#include <bsoncxx/stdx/string_view.hpp>
#include <bsoncxx/types.hpp>
#include <bsoncxx/types/value.hpp>


using namespace bsoncxx;

int main(int argc, char **argv) {
    //sio::client h;

    //h.set_open_listener([&]() {
    //    sio::socket::ptr s = h.socket();
    //    
    //    sio::message::ptr p = sio::bool_message::create(true);
    //    s->emit("cpp_client", p);
    //    std::cout << "emit a cpp_client" << std::endl;

    //    s->on("server_get_page", sio::socket::event_listener_aux([s](string const& name, message::ptr const& data,
    //                    bool isAck,message::list &ack_resp) {
    //        string s1 = data->get_string();
    //        cout << "recv:" << s1 << endl;
    //        std::string view{"{{#names}}Hi {{name}}!\n{{/names}}"};
    //        mstch::map context{
    //            {"names",  mstch::array{
    //                mstch::map{{"name", std::string{s1}}}
    //            }}
    //        };
    //        sio::message::ptr p = sio::string_message::create(string(mstch::render(view, context)));
    //        s->emit("cpp_push_page", p);
    //    }));
    //});

    //h.connect("http://127.0.0.1:8088");
    using namespace builder::stream;

    auto build_doc = builder::stream::document{};
    // {
    //     "_id" : 1,
    //     "name" : { "first" : "John", "last" : "Backus" },
    //     "contribs" : [ "Fortran", "ALGOL", "Backus-Naur Form", "FP" ],
    //     "awards" : [
    //                {
    //                  "award" : "W.W. McDowell Award",
    //                  "year" : 1967,
    //                  "by" : "IEEE Computer Society"
    //                },
    //                { "award" : "Draper Prize",
    //                  "year" : 1993,
    //                  "by" : "National Academy of Engineering"
    //                }
    //     ]
    // }
    auto doc_value = build_doc << "_id" << 1 << "name" << open_document << "first"
              << "John"
              << "last"
              << "Backus" << close_document << "contribs" << open_array << "Fortran"
              << "ALGOL"
              << "Backus-Naur Form"
              << "FP" << close_array << "awards" << open_array << open_document << "award"
              << "W.W. McDowell Award"
              << "year" << 1967 << "by"
              << "IEEE Computer Society" << close_document << open_document << "award"
              << "Draper Prize"
              << "year" << 1993 << "by"
              << "National Academy of Engineering" << close_document << close_array << finalize;

    //bsoncxx::document::value doc_value = build_doc;
    auto doc = doc_value.view();

    // Once we have the document view, we can use ["key"] or [index] notation to reach into nested
    // documents or arrays.
    auto awards = doc["awards"];
    auto first_award_year = awards[0]["year"];
    auto second_award_year = doc["awards"][1]["year"];
    auto last_name = doc["name"]["last"];    
    cout << bsoncxx::to_json(doc["_id"]) << endl; 
    cout << bsoncxx::to_json(first_award_year) << endl; 
}
