#include "daily_movie.hpp"
void Douban_d::get_url(){
    string main_page = "https://movie.douban.com";
    string info = craw->getPageContent(main_page);
    info = get_pattern(info, "<div class=\"screening-bd\">(.|\\r|\\n)*?<div class=\"gaia gaia-lite gaia-movie\">");
    get_pieces(info, "<li class=\"ui-slide-item(.|\\r|\\n)*?<li class=\"ticket_btn\">");
}
void Douban_d::deal_piece(string info){
    string name0 = get_pattern(info, "data-title.*?data-release");
    name.push_back(get_keyinfo(name0, '"', '"'));
    
    string img0 = get_pattern(info, "http.*?jpg");
    img.push_back(turn_to_char(img0));
    
    string url0 = get_pattern(info, "http.*?from=showing");
    url.push_back(turn_to_char(url0));
    
    string rate0 = get_pattern(info, "data-rate.*?data-star");
    rate.push_back(get_keyinfo(rate0, '"', '"'));
}

void Imdb_d::get_url(){
    string main_page = "http://www.imdb.com/movies-in-theaters/?ref_=nv_mv_inth_1";
    string info =craw->getPageContent(main_page);
    info = get_pattern(info, "<h3>Opening This Week(.|\\r|\\n)*?<div class=\" see-more\">");
    get_pieces(info, "<img class=\"poster shadowed\"(.|\\r|\\n)*?<td class=\"overview-bottom\">");
}

void Imdb_d::deal_piece(string info){
    string name0 = get_pattern(info, "itemprop='url'>.*?</a></h4>");
    name.push_back(get_keyinfo(name0, '>', '<'));
    
    string url0 = get_pattern(info, "<h4 itemprop=\"name\">.*?_tt\"");
    url0 = get_pattern(url0, "/title.*?_tt");
    url0 = "http://www.imdb.com" + url0;
    url.push_back(turn_to_char(url0));
    
    string rate0 = get_pattern(info, "favorable\">.*?</span>");
    rate.push_back(get_keyinfo(rate0, '>', '<'));
    
    string img0 = get_pattern(info, "http.*?jpg");
    img.push_back(turn_to_char(img0));
    
}
