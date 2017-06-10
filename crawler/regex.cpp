//
//  regex.cpp
//  Movie_Crawler
//
//  Created by 王诗媛 on 2017/5/31.
//  Copyright © 2017年 王诗媛. All rights reserved.
//

#include "regex.hpp"

char* REGEX::turn_to_char(string str){
    cout<<str.size()<<endl;
    char *tmp = new char[str.size()+1];
    //cout<<str.c_str()<<endl;
    memcpy(tmp, str.c_str(), str.size() + 1);
    //cout<<tmp<<endl;
    cout << "23333" << endl;
    return tmp;
}

string REGEX::get_pattern(string page, string pattern){
    cout << "1.1" << endl;
    pattern = "[[:alpha:]]*" + pattern + "[[:alpha:]]*";
    regex r(pattern);
    sregex_iterator it(page.begin(), page.end(), r);
    cout << "1.2" << endl;
    string str = it->str();
    cout << "1.3" << endl;
    return str;
}

void REGEX::get_pieces(string info, string pattern){
    pattern = "[[:alpha:]]*" + pattern + "[[:alpha:]]*";
    regex r(pattern);
    for(sregex_iterator it(info.begin(), info.end(), r), end; it != end; ++it){
        string str = it->str();
        deal_piece(str);
    }
}

void REGEX::get_pieces(string info, string pattern, vector<char *> &v){
    pattern = "[[:alpha:]]*" + pattern + "[[:alpha:]]*";
    regex r(pattern);
    for(sregex_iterator it(info.begin(), info.end(), r), end; it != end; ++it){
        string str = it->str();
        v.push_back(get_keyinfo(str, '>', '<'));
    }
}


char *REGEX::get_keyinfo(string str, char pre, char aft){
    char *tmp = turn_to_char(str);
    return get_keyinfo(tmp, pre, aft);
}

char *REGEX::get_keyinfo(char *src, char pre, char aft){  //获得pre aft之间的信息
    while(*src)
    {
        if(*src == pre)
            break;
        src ++;
    }
    src ++;
    char *fp = new char[20];
    char *it = fp;
    while (*src) {
        if(*src == aft)
            break;
        if (/*(*src != ' ') && */(*src != '\n') && (*src != '\r')) { // 如果不是空格就复制
            *it = *src;
            it++;
        }
        src++;
    }
    *it = '\0' ; //封闭字符串
    //cout<<fp<<endl;
    cout << "ahah" << endl;
    return fp;
}

//获取电影url的

