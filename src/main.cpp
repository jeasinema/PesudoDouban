/*-----------------------------------------------------
 File Name : main.cpp
 Purpose :
 Creation Date : 20-05-2017
 Last Modified : Sun May 21 15:14:44 2017
 Created By : Jeasine Ma [jeasinema[at]gmail[dot]com]
-----------------------------------------------------*/
#include <iostream>

#include <bsoncxx/builder/stream/document.hpp>
#include <bsoncxx/json.hpp>

#include <mongocxx/client.hpp>
#include <mongocxx/instance.hpp>

#include <mstch/mstch.hpp>

#include "sio_client.h"
#include "sio_socket.h"


using namespace sio;

int main(int, char**) {
    mongocxx::instance inst{};
    mongocxx::client conn{mongocxx::uri{}};

    bsoncxx::builder::stream::document document{};

    auto collection = conn["testdb"]["testcollection"];
    document << "hello" << "world";

    collection.insert_one(document.view());
    auto cursor = collection.find({});

    for (auto&& doc : cursor) {
        std::cout << bsoncxx::to_json(doc) << std::endl;
    }
    
    std::string view{"{{#names}}Hi {{name}}!\n{{/names}}"};
    mstch::map context{
    {"names", mstch::array{
      mstch::map{{"name", std::string{"Chris"}}},
      mstch::map{{"name", std::string{"Mark"}}},
      mstch::map{{"name", std::string{"Scott"}}},
    }}
  };
  
  std::cout << mstch::render(view, context) << std::endl;
  sio::client h;
  h.connect("http://127.0.0.1:3000");
}
