// Copyright 2015 MongoDB Inc.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
// http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#include <cstdlib>
#include <iostream>

#include "rapidjson/document.h"

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

int main(int, char**) {
    using namespace builder::stream;

    builder::stream::document build_doc;
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
    build_doc << "_id" << 1 << "name" << open_document << "first"
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
              << "National Academy of Engineering" << close_document << close_array;

    bsoncxx::document::view doc = build_doc.view();
    std::cout << to_json(doc) << std::endl;
    rapidjson::Document document;
    document.Parse(to_json(doc).c_str());
    std::cout << document["_id"].GetInt() << std::endl;
    for (auto& i : document["contribs"].GetArray()) {
        std::cout << i.GetString();
    }

    // Once we have the document view, we can use ["key"] or [index] notation to reach into nested
    // documents or arrays.
    auto awards = doc["awards"];
    auto first_award_year = awards[0]["year"];
    auto second_award_year = doc["awards"][1]["year"];
    auto last_name = doc["name"]["last"];

    // If the key doesn't exist, or index is out of bounds, we get invalid elements.
    auto invalid1 = doc["name"]["middle"];
    auto invalid2 = doc["contribs"][1000];
    if (invalid1 || invalid2) {
        BSONCXX_UNREACHABLE;  // Not reached.
    }

    // Similarly, indexed access (either by string or numeric index) into a type that is not
    // a document or an array yields invalid eleemnts.

    auto invalid3 = doc["_id"]["invalid"];
    auto invalid4 = doc["name"][3];
    if (invalid3 || invalid4) {
        BSONCXX_UNREACHABLE;  // Not reached.
    }

    // Make all variables used.
    return (awards && first_award_year && second_award_year && last_name) ? EXIT_SUCCESS
                                                                          : EXIT_FAILURE;
}
