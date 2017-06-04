#include "regex.hpp"
#include "CRAW.hpp"
class Daily_movie : public REGEX{
public:
    vector<char *> url;
    vector<char *> name;
    vector<char *> rate;
    vector<char *> img;
    CRAW *craw;
    
    virtual void get_url() = 0;
};

class Douban_d : public Daily_movie{
public:
    Douban_d(){
        craw = new CRAW;
    }
    void get_url();
    void deal_piece(string info);
};

class Imdb_d : public Daily_movie{
public:
    Imdb_d(){
        craw = new CRAW;
    }
    void get_url();
    void deal_piece(string info);
};
