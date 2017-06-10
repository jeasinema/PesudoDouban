#include "actor.hpp"

void Douban_a::get_data(string url){
    string info = get_pattern(url, "<div id=\"headline\" class=\"item\">(.|\\r|\\n)*?<div class=\"info\">(.|\\r|\\n)*?</div>");
    deal_info(info);
}

void Douban_a::deal_info(string info){
    //获取演员名
    string name = get_pattern(info, "class=\"nbg\" title=\".*?\"");
    name = name.replace(0, 19, "");
    char *n = turn_to_char(name);
    unsigned long pos = name.find("\"");
    n[pos] = '\0';
    actor->name = n;
    cout<<n<<endl;
    //获取img地址
    string img = get_pattern(info, "http.*?large.*?.jpg");
    actor->imgurl = turn_to_char(img);
    
    //获取演员信息
    match_tag(info);
    
}

void Douban_a::match_tag(string info){
    string pattern("<li>(.|\\r|\\n)*?</li>");
    pattern = "[[:alpha:]]*" + pattern + "[[:alpha:]]*";
    regex r(pattern);
    for(sregex_iterator it(info.begin(), info.end(), r), end; it != end; ++it){
        char *tag = get_tag(it->str());
        char *content = get_content(it->str());
        match(tag, content);
    }
}

char* Douban_a::get_tag(string li){
    string n1 = get_pattern(li, "span>.*?</span");
    char *tag = get_keyinfo(n1, '>', '<');
    return tag;
}

char* Douban_a::get_content(string li){ //找</span>: * <li>之间的信息
    unsigned long pos = li.find(":");
    li = li.replace(0, pos + 1, "");
    char *con = turn_to_char(li);
    char *fp = new char[20];
    char *it = fp;
    while (*con) {
        if(*con == '<')
            break;
        if ((*con != ' ') && (*con != '\n') && (*con != '\r')) { // 如果不是空格就复制
            *it = *con;
            it++;
        }
        con++;
    }
    *it = '\0' ; //封闭字符串
    return fp;
}

void Douban_a::match(char *tag, char *content){
    if(strcmp(tag, "性别") == 0)
    {
        actor->sex = content;
        return;
    }
    if(strcmp(tag, "星座")){
        actor->constellation = content;
        return;
    }
    if(strcmp(tag, "出生日期")){
        actor->birthday = content;
        return;
    }
    if(strcmp(tag, "出生地")){
        actor->birthplace = content;
        return;
    }
    if(strcmp(tag, "职业")){
        actor->occupation.push_back(content);
        return;
    }
    if(strcmp(tag, "更多外文名")){
        actor->foreignName = content;
        return;
    }
    if(strcmp(tag, "更多中文名")){
        actor->ChineseName = content;
        return;
    }
    if(strcmp(tag, "家庭成员")){
        actor->familyMember = content;
        return;
    }
    if(strcmp(tag, "imdb编号")){
        get_imdbCode(content);
        return;
    }
    if(strcmp(tag, "官方网站")){
        get_selfPage(content);
        return;
    }
}

void Douban_a::get_imdbCode(string imdb){
    string code = get_pattern(imdb, "nm(\\d)*");
    actor->imdbCode = turn_to_char(code);
}
void Douban_a::get_selfPage(string page){
    string url = get_pattern(page, "http[^\"]*");
}

void Imdb_a::get_data(string html){
    string info = get_pattern(html, "span class=\"itemprop\" itemprop=\"name\">(.|\\r|\\n)*?<td id=\"overview-middle\">");
    deal_info(info);
}

void Imdb_a::deal_info(string info){
    string name = get_pattern(info, "itemprop=\"name\">.*?</span>");
    actor->name = get_keyinfo(name, '>', '<');
    
    get_pieces(info, "itemprop=\"jobTitle\">(.|\\r|\\n)*?</span>", actor->occupation);
    
    string birthday = get_pattern(info, "<time datetime=.*?itemprop");
    actor->birthday = get_keyinfo(birthday, '"', '"');
    
    string birthplace = get_pattern(info, "nm_ov_bth_place(.|\\r|\\n)*?</a>");
    actor->birthplace = get_keyinfo(birthplace, '>', '<');
    
    string img = get_pattern(info, "http.*?jpg");
    actor->imgurl = turn_to_char(img);
}
