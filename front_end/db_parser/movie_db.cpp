/*-----------------------------------------------------
 File Name :
 Purpose :
 Creation Date : 22-05-2017
 Last Modified : Mon May 22 12:34:40 2017
 Created By : Jeasine Ma [jeasinema[at]gmail[dot]com]
-----------------------------------------------------*/
#include "db_parser/movie_db.h"
#include "db_parser/metadata.h"

namespace persudo {
namespace db_parser {

shared_ptr<MovieData> MovieDB::get_movie_data(const string& movie_name) {
    return std::make_shared<MovieData>();
}

vector<string> MovieDB::search_movie(const string& movie_name) {
    return vector<string>{""};
}

}
}
