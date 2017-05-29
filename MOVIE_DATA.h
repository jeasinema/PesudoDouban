#include <iostream>
#include <vector>
using namespace std;

struct MOVIE{
    char *title;
    vector<char*> director;
    vector<char*> writer;
    vector<char*> actor;
    vector<char*> genre;
    vector<char*> date;
    char *duration;
    char *imdb;
};

class MOVIE_DATA{
    MOVIE *movie;
public:
    MOVIE_DATA(){
        movie = new MOVIE;
    }
    char *turn_to_char(string str);
    
    string get_pattern(string page, string pattern);
    void get_data(string url);
    void deal_info(string info);
    void get_piece(string info, string pattern, vector<char*> &v);
    char *get_keyinfo(char *str);
    char *get_keyinfo(string str);
};
