#ifndef actor_data_h
#define actor_data_h

#include <iostream>
#include <vector>
using namespace std;

struct ACTOR{
    char *name;
    char *imgurl;
    char *sex;
    char *constellation;
    char *birthday;
    char *birthplace;
    char *occupation;
    char *foreignName;
    char *ChineseName;
    char *familyMember;
    char *imdbCode;
    char *selfPage;
};

class ACTOR_DATA{
    ACTOR *actor;
public:
    ACTOR_DATA(){
        actor = new ACTOR;
    }
    char *turn_to_char(string str);
    string get_pattern(string page, string pattern);
    
    char *get_keyinfo(char *str);
    char *get_keyinfo(string str);
    
    void get_data(string url);
    void deal_info(string info);
    void match_tag(string info);
    
    char* get_tag(string li);
    char* get_content(string li);
    void match(char *tag, char *content);
    
    void get_imdbCode(string imdb);
    void get_selfPage(string page);
};

#endif /* actor_data_h */
