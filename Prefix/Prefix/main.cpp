//
//  main.cpp
//  Prefix
//
//  Created by Kaushik Isukapalli on 5/21/21.
//  Copyright © 2021 Kaushik Isukapalli. All rights reserved.
//

#include <iostream>
#include <vector>
using namespace std;

string longestCommonPrefix(vector<string>& strs) {
    int minLength = strs[0].length();
    for (int i = 1; i < strs.size(); i++) {
        if (strs[i].length() < minLength) {
            minLength = strs[i].length();
        }
    }
    string prefix = "";
    for (int i = 0; i < minLength; i++) {
        int j = 0;
        while ((j < strs.size()-1) && (strs[j][i] == strs[j+1][i])) {
            j++;
        }
        if (j == strs.size()-1) {
            prefix += strs[0][i];
        }
        else {
            return prefix;
        }
    }
    return prefix;
}

int main(int argc, const char * argv[]) {
    vector<string> input;
    input.push_back("flies");
    input.push_back("fliw");
    input.push_back("flight");
    std::cout << longestCommonPrefix(input) << endl;
    return 0;
}
