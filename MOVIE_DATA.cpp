#include "movie_data.h"
#include <string>
#include <regex>
#include <iostream>
using namespace std;

string MOVIE_DATA::get_pattern(string page, string pattern){
    pattern = "[[:alpha:]]*" + pattern + "[[:alpha:]]*";
    regex r(pattern);
    sregex_iterator it(page.begin(), page.end(), r);
    string str = it->str();
    return str;
}

void MOVIE_DATA::get_data(string html){
    
    //获得title信息
    string title = get_pattern(html, "<title>(.|\\r|\\n)*?</title>");
    char *tmp = turn_to_char(title);
    movie->title = get_keyinfo(tmp);
    
    //获得info<div>
    string info = get_pattern(html, "(<div id=\"info\">)(.|\\r|\\n)*?(</div>)");
    deal_info(info);//处理info字段
}

void MOVIE_DATA::deal_info(string info)
{
    //获得导演信息
    get_piece(info, "\"v:directedBy\">.*?</a>", movie->director);
    //获得编剧信息
    get_piece(info, "<a href=\"/celebrity/\\d{7}/\">.*?</a>", movie->writer);
    //获得演员信息
    get_piece(info, "v:starring\">.*?</a", movie->actor);
    //获取类型信息
    get_piece(info, "v:genre\">.*?</span", movie->genre);
    //获取电影上映时间
    get_piece(info, "v:initialReleaseDate\" content=\".*?\">.*?</span", movie->date);
    //获取时长
    string duration = get_pattern(info, "v:runtime\" content=\"\\d*?\">.*?</span");
    movie->duration = get_keyinfo(duration);
    //获取imdb链接
    
}

void MOVIE_DATA::get_piece(string info, string pattern, vector<char *> &v){
    pattern = "[[:alpha:]]*" + pattern + "[[:alpha:]]*";
    regex r(pattern);
    for(sregex_iterator it(info.begin(), info.end(), r), end; it != end; ++it){
        string str = it->str();
        v.push_back(get_keyinfo(str));
    }
}

char* MOVIE_DATA::turn_to_char(string str){
    cout<<str.size()<<endl;
    char *tmp = new char[str.size()+1];
    cout<<str.c_str()<<endl;
    memcpy(tmp, str.c_str(), str.size() + 1);
    cout<<tmp<<endl;
    return tmp;
}

char *MOVIE_DATA::get_keyinfo(string str){
    char *tmp = turn_to_char(str);
    return get_keyinfo(tmp);
}

char *MOVIE_DATA::get_keyinfo(char *src){  //获得><之间的信息
    while(*src)
    {
        if(*src == '>')
            break;
        src ++;
    }
    src ++;
    char *fp = new char[20];
    char *it = fp;
    while (*src) {
        if(*src == '<')
            break;
        if ((*src != ' ') && (*src != '\n') && (*src != '\r')) { // 如果不是空格就复制
            *it = *src;
            it++;
        }
        src++;
    }
    *it = '\0' ; //封闭字符串
    cout<<fp<<endl;
    return fp;
}

















