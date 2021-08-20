//
//  main.cpp
//  WordPattern
//
//  Created by Kaushik Isukapalli on 7/16/21.
//  Copyright © 2021 Kaushik Isukapalli. All rights reserved.
//

#include <iostream>
using namespace std;
#include <map>

bool wordPattern(string pattern, string s) {
    map<char, string> cs;
    map<string, char> sc;
    int i = 0;
    int j = 0;
    int k = 0;
    while (j < s.length()) {
        if (s[j] == ' ') {
            string current = s.substr(i, j-i);
            if (cs[pattern[k]].compare("") == 0 && (int) sc[current] == 0) {
                cs[pattern[k]] = current;
                sc[current] = pattern[k];
                i = j+1;
                k++;
            }
            else if (cs[pattern[k]].compare(current) != 0 || sc[current] != pattern[k]) {
                return false;
            }
        }
        j++;
    }
    return true;
}

int main(int argc, const char * argv[]) {
    cout << wordPattern("abba", "dog cat cat dog") << endl;
    return 0;
}
