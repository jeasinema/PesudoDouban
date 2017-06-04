#ifndef regex_hpp
#define regex_hpp

#include <stdio.h>
#include <string>
#include <regex>
#include <iostream>

using namespace std;

class REGEX{
    
public:
    char *turn_to_char(string str);
    string get_pattern(string page, string pattern);
    char *get_keyinfo(char *str, char pre, char aft);
    char *get_keyinfo(string str, char pre, char aft);
    
    void get_pieces(string info, string pattern);
    void get_pieces(string info, string pattern, vector<char*> &v);
    
    virtual void deal_piece(string info) = 0;
};


#endif /* regex_hpp */
