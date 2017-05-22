/*-----------------------------------------------------
 File Name : metadata.h
 Purpose :
 Creation Date : 21-05-2017
 Last Modified : Mon May 22 12:18:06 2017
 Created By : Jeasine Ma [jeasinema[at]gmail[dot]com]
-----------------------------------------------------*/
#ifndef METADATA_H
#define METADATA_H 

#include <string>
#include <vector>
#include <map>
#include <memory>

namespace persudo {
namespace db_parser {

using std::string;
using std::vector;
using std::map;
using std::shared_ptr;
using std::weak_ptr;

class MetaData {
public:
    inline virtual void foo() {};
};

struct MovieCritic {
    string user_name;
    string date;
    string detail;
};

struct PersonData {
    string name;
    // prefix + id = url
    string image_id;
};

struct MovieData {
    string movie_name;
    string movie_date; // YYYY-MM
    string movie_time; // xxx min
    int movie_rate; // 0 to 5 stars
    string movie_level;
    
    // prefix + id = url
    string movie_poster_id;
    string movie_name_id;
    
    vector<string> movie_class;
    shared_ptr<string> movie_abstract;
    shared_ptr<string> movie_detail;

    vector<MovieCritic> movie_critic;

    vector<PersonData> movie_star;
    vector<PersonData> movie_director;
    vector<PersonData> movie_writer;

    // we will not extract movie_relate in movie_relate
    vector<shared_ptr<MovieData>> movie_relate;
};

class PersudoData : public MetaData {
public:
    vector<shared_ptr<MovieData>> movie_data;
};

}
}


#endif /* METADATA_H */
