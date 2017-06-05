//
//  movie.hpp
//  Movie_Crawler
//
//  Created by 王诗媛 on 2017/5/31.
//  Copyright © 2017年 王诗媛. All rights reserved.
//

#ifndef movie_hpp
#define movie_hpp

#include <stdio.h>
#include <vector>
#include <iostream>
#include "regex.hpp"
using namespace std;

struct MOVIE{
    char *title;
    vector<char*> director;
    vector<char*> writer;
    vector<char*> actor;

    char *getTitle() const;

    const vector<char *, allocator<char *>> &getDirector() const;

    const vector<char *, allocator<char *>> &getWriter() const;

    const vector<char *, allocator<char *>> &getActor() const;

    const vector<char *, allocator<char *>> &getGenre() const;

    const vector<char *, allocator<char *>> &getDate() const;

    char *getDuration() const;

    char *getPoster() const;

    char *getImdb() const;

    vector<char*> genre;
    vector<char*> date;
    char *duration;
    char *poster;
    char *imdb;
};

class MOVIE_DATA : public REGEX{
public:
    MOVIE *movie;
    MOVIE_DATA(){
        movie = new MOVIE;
    }
    void deal_piece(string info){}
    virtual void get_data(string url) = 0;
    void print_info();
};

class Douban_m : public MOVIE_DATA{
public:
    void get_data(string url);
    void deal_info(string info);
};

class Imdb_m : public MOVIE_DATA{
public:
    void get_data(string url);
    void deal_info(string info);
};
#endif /* movie_hpp */
