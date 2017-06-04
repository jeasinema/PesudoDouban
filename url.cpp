#include "url.hpp"
#include <sstream>

void Douban::get_url(string keyword){
    string url0 =  "https://www.douban.com/tag/" + keyword + "/movie";
    string str;
    for(int i = 0; i < 300; i = i + 15)
    {
        stringstream stream;
        stream<<i;
        str=stream.str();
        url0 = url0 + "?start=" + str;
        string info = craw->getPageContent(url0);
        get_pieces(info, "(<dl>)(.|\\r|\\n)*?(</dl>)");
    }
}

void Douban::deal_piece(string info){
    string url0 = get_pattern(info, "http.*?from=tag_all");
    url.push_back(turn_to_char(url0));
    
    string name0 = get_pattern(info, "class=\"title\".*?</a>");
    name.push_back(get_keyinfo(name0, '>', '<'));
    
    string tag0 = get_pattern(info, "<div class=\"desc\">(.|\\r|\\n)*?</div>");
    tag.push_back(get_keyinfo(tag0, '>', '<'));
    
    string img0 = get_pattern(info, "http.*?jpg");
    img.push_back(turn_to_char(img0));
    
}

void Imdb::get_url(string keyword){
    string url0 = "http://www.imdb.com/search/keyword?keywords=" + keyword + "&sort=moviemeter,asc&mode=detail&page=";
    string str;
    for(int i = 1; i < 5; i++){
        stringstream stream;
        stream<<i;
        str = stream.str();
        url0 = url0 + str + "&ref_=kw_nxt";
        string info = craw->getPageContent(url0);
        get_pieces(info, "class=\"loadlate\"(.|\\r|\\n)*?<div class=\"ratings-bar\">");
    }
}

void Imdb::deal_piece(string info){
    string url0 = get_pattern(info, "/title/.*?ref_=kw_li_tt");
    url0 = "http://www.imdb.com" + url0;
    url.push_back(turn_to_char(url0));
    
    string name0 = get_pattern(info, ">.*?</a>");
    name.push_back(get_keyinfo(name0, '>', '<'));
    
    string tag0 = get_pattern(info, "<span class=\"genre\">(.|\\r|\\n)*?</span>");
    tag.push_back(get_keyinfo(tag0, '>', '<'));
    
    string img0 = get_pattern(info, "http.*?.jpg");
    img.push_back(turn_to_char(img0));
}
