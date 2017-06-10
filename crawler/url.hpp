//
//  url.hpp
//  Movie_Crawler
//
//  Created by 王诗媛 on 2017/5/31.
//  Copyright © 2017年 王诗媛. All rights reserved.
//

#ifndef url_hpp
#define url_hpp

#include <stdio.h>
#include <vector>
#include "regex.hpp"
#include "CRAW.hpp"

using namespace std;

class URL : public REGEX{
public:
    vector<char *> url;
    vector<char *> name;
    vector<char *> tag;
    vector<char *> img;
    CRAW *craw;
    
    virtual void get_url(string keyword) = 0;
};

class Douban : public URL{
public:
    Douban(){
        craw = new CRAW;
    }
    void get_url(string keyword);
    void deal_piece(string info);
    
};

class Imdb : public URL{
public:
    Imdb(){
        craw = new CRAW;
    }
    void get_url(string keyword);
    void deal_piece(string info);
};
#endif /* url_hpp */
