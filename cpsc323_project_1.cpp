//
//  main.cpp
//  cpsc323_project_1
//
//  Created by Daniel Bravo on 2/17/17.
//  Copyright © 2017 Daniel Bravo. All rights reserved.
//

#include <iostream>
#include "resources.h"

using namespace std;

void testToken(string cntrl, string test);

int main(int argc, const char * argv[]) {
    string test ="(:token 3 string :str \"ASCII:\")";
    
    Token t = *new Token(); // (:token 3 string :str "ASCII:")
    t.ln = 3;
    t.id = "string";
    t.str= "ASCII:";
    //    t.ix = 4;
    
    
    
    
    cout << t.to_string() << endl;
    testToken("(:token 3 string :str \"ASCII:\")", t.to_string());
    cout << endl;
}

void testToken(string cntrl, string test) {
    if(cntrl.compare(test) == 0)
        cout << "Success! Token are equal";
    else
        cout << "You failed";
}

