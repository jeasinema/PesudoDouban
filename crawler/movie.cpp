 #include "movie.hpp"
void Douban_m::get_data(string html){
    //获得title信息
    string title = get_pattern(html, "<title>(.|\\r|\\n)*?</title>");
    char *tmp = turn_to_char(title);
    movie->title = get_keyinfo(tmp, '>', '<');
    
    string poster = get_pattern(html, "<div id=\"mainpic\" class=\"\">(.|\\r|\\n)*?</div>");
    poster = get_pattern(poster, "http.*?jpg");
    movie->poster = turn_to_char(poster);
    
    //获得info<div>
    string info = get_pattern(html, "(<div id=\"info\">)(.|\\r|\\n)*?(</div>)");
    deal_info(info);//处理info字段
    cout << "233" << endl;
    //cout << movie->getImdb() << endl;
    cout << "fuck" << endl;
}

void Douban_m::deal_info(string info)
{
    //获得导演信息
    get_pieces(info, "\"v:directedBy\">.*?</a>", movie->director);
    //获得编剧信息
    get_pieces(info, "<a href=\"/celebrity/\\d{7}/\">.*?</a>", movie->writer);
    //获得演员信息
    get_pieces(info, "v:starring\">.*?</a", movie->actor);
    //获取类型信息
    get_pieces(info, "v:genre\">.*?</span", movie->genre);
    //获取电影上映时间
    get_pieces(info, "v:initialReleaseDate\" content=\".*?\">.*?</span", movie->date);
    //获取时长
    string duration = get_pattern(info, "v:runtime\" content=\"\\d*?\">.*?</span");
    movie->duration = get_keyinfo(duration, '>', '<');
    //获取imdb链接
}

void Imdb_m::get_data(string html){
    string info = get_pattern(html, "<h1 itemprop=\"name\"(.|\\r|\\n)*?See full cast & crew(.|\\r|\\n)*?</div>");
    deal_info(info);
}

void Imdb_m::deal_info(string info){
    string title = get_pattern(info, "class=\"\">.*?&nbsp");
    movie->title = get_keyinfo(title, '>', '&');
    
    string poster = get_pattern(info, "<div class=\"poster\">(.|\\r|\\n)</div>");
    poster = get_pattern(poster, "http.*?jpg");
    movie->poster = turn_to_char(poster);
    
    string duration = get_pattern(info, "<time(.|\\r|\\n)*?</time>");
    movie->duration = get_keyinfo(duration, '>', '<');
    
    get_pieces(info, "itemprop=\"genre\".*?</span", movie->genre);
    
    string Director = get_pattern(info, "Director(.|\\r|\\n)*?</div>");
    get_pieces(Director, "itemprop=\"name\">.*?</span>", movie->director);
    
    string Creator = get_pattern(info, "Creator(.|\\r|\\n)*?</div>");
    get_pieces(Creator, "itemprop=\"name\">.*?</span>", movie->director);
    
    string Writer = get_pattern(info, "Writer(.|\\r|\\n)*?</div>");
    get_pieces(Writer, "itemprop=\"name\">.*?</span>", movie->writer);
    
    string Stars = get_pattern(info, "Star(.|\\r|\\n)*?</div>");
    get_pieces(Stars, "itemprop=\"name\">.*?</span>", movie->actor);
    
    string date = get_pattern(info, "See more release dates(.|\\r|\\n)*?<meta");
    movie->date.push_back(get_keyinfo(date, '>', '<'));
}

 void MOVIE_DATA::print_info() {
     if(movie == 0)
     {
         cout << "failed." << endl;
         return;
     }
     cout << "imdb: " << movie->imdb << endl;
     cout << "duration: " << movie->duration << endl;
     cout << "title: " << movie->title << endl;
     cout << "poster: " << movie->poster << endl;
     for (auto &e: movie->actor)
     {
         cout << "actor: " << e << endl;
     }
     for (auto &e: movie->date)
     {
         cout << "date: " << e << endl;
     }
     for (auto &e: movie->director)
     {
         cout << "director: " << e << endl;
     }
     for (auto &e: movie->genre)
     {
         cout << "genre: " << e << endl;
     }
     for (auto &e: movie->writer)
     {
         cout << "writer: " << e << endl;
     }
 }

 char *MOVIE::getTitle() const {
     return title;
 }

 const vector<char *, allocator<char *>> &MOVIE::getDirector() const {
     return director;
 }

 const vector<char *, allocator<char *>> &MOVIE::getWriter() const {
     return writer;
 }

 const vector<char *, allocator<char *>> &MOVIE::getActor() const {
     return actor;
 }

 const vector<char *, allocator<char *>> &MOVIE::getGenre() const {
     return genre;
 }

 const vector<char *, allocator<char *>> &MOVIE::getDate() const {
     return date;
 }

 char *MOVIE::getDuration() const {
     return duration;
 }

 char *MOVIE::getPoster() const {
     return poster;
 }

 char *MOVIE::getImdb() const {
     return imdb;
 }
