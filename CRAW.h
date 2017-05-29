#ifndef craw_h
#define craw_h

#include <iostream>
#include <string>
#include <netdb.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <curl/curl.h>
#include <cstring>
#include <cstdlib>

using namespace std;

struct string0 {
    char *ptr;
    size_t len;
};

class CRAW
{
public:
    //void parseHostAndPagePath(const string url, string &hostUrl, string &pagePath);//提取网页路径
    
    void init_string(struct string0 *s);
    static size_t get_response(void *ptr, size_t size, size_t nmemb, struct string0 *s);
    
    string getPageContent(string url);//获取某一个网页的源码
};

class douban : public CRAW{
public:
    using CRAW::CRAW;
    
};

#endif /* crawler_h */
