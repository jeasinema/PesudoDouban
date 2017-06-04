//
//  actor.hpp
//  Movie_Crawler
//
//  Created by 王诗媛 on 2017/5/31.
//  Copyright © 2017年 王诗媛. All rights reserved.
//

#ifndef actor_hpp
#define actor_hpp

#include <stdio.h>
#include <iostream>
#include <vector>
#include "regex.hpp"
using namespace std;

struct ACTOR{
    char *name;
    char *imgurl;
    char *sex;
    char *constellation;
    char *birthday;
    char *birthplace;
    vector<char*> occupation;
    char *foreignName;
    char *ChineseName;
    char *familyMember;
    char *imdbCode;
    char *selfPage;
};
class ACTOR_DATA : public REGEX{
public:
    ACTOR *actor;
    ACTOR_DATA(){
        actor = new ACTOR;
    }
    void deal_piece(string info){}
    virtual void get_data(string html) = 0;
};

class Douban_a : public ACTOR_DATA{
public:
    
    void get_data(string url);
    void deal_info(string info);
    void match_tag(string info);
    
    char* get_tag(string li);
    char* get_content(string li);
    void match(char *tag, char *content);
    
    void get_imdbCode(string imdb);
    void get_selfPage(string page);
};

class Imdb_a : public ACTOR_DATA{
public:
    void get_data(string html);
    void deal_info(string info);
};
#endif /* actor_hpp */
