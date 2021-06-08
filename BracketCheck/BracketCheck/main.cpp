//
//  main.cpp
//  BracketCheck
//
//  Created by Kaushik Isukapalli on 5/14/21.
//  Copyright © 2021 Kaushik Isukapalli. All rights reserved.
//

#include <iostream>
#include <stack>
#include <cstring>
#include <cmath>
using namespace std;

// bool bracketCheck(string input)
bool bracketCheck(char *input) {
    
    stack<char> brackets;
    while (*input) {
        if (*input == '(' || *input == '[' || *input == '{') {
            brackets.push(*input);
        }
        else {
            if (brackets.empty()) {
                return false;
            }
            else if (((int(*input) - int(brackets.top())) != 1) && ((int(*input) - int(brackets.top())) != 2)) {
                return false;
            }
            else {
                brackets.pop();
            }
        }
        input++;
    }
    if (brackets.empty()) {
        return true;
    }
    return false;
}

int main(int argc, const char * argv[]) {
    string i = "😂";
    cout << "\u1f293" << endl;
}
