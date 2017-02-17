//
//  Header.h
//  cpsc323_project_1
//
//  Created by Daniel Bravo on 2/17/17.
//  Copyright © 2017 Daniel Bravo. All rights reserved.
//

#ifndef resources_h
#define resources_h

#endif /* Header_h */

#include <stdio.h>
#include <string>

using namespace std;

struct Token {
    int ln;         // line nubmer
    string id;      // id based on grammer
    int ix = 0;         // optional; index number of token
    string str;     // optional; actual string
    
    string to_string() {
        string ix_s;
        string str_s;
        if(ix == 0)
            ix_s = "";
        else
            ix_s = ":ix " + std::to_string(ix) + " ";
        if(str.empty())
            str_s = "";
        else
            str_s = ":str \"" + str + "\"";
        
        return "(:token " + std::to_string(ln) + " " + id + " " + ix_s + str_s + ")";
    }
};

void print_token();
Token peek_token();
