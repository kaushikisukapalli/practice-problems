//
//  main.cpp
//  RomanToInt
//
//  Created by Kaushik Isukapalli on 5/21/21.
//  Copyright © 2021 Kaushik Isukapalli. All rights reserved.
//

#include <iostream>
using namespace std;

int romanToInt(string s) {
    int number = 0;
    for (int i = 0; i < s.length(); i++) {
        char current = s[i];
        switch (current) {
            case 'I':
                if ((i < s.length()-1) && (s[i+1] == 'V' || s[i+1] == 'X')) {
                    number -= 1;
                }
                else {
                    number += 1;
                }
                break;
            case 'V':
                number += 5;
                break;
            case 'X':
                if ((i < s.length()-1) && (s[i+1] == 'L' || s[i+1] == 'C')) {
                    number -= 10;
                }
                else {
                    number += 10;
                }
                break;
            case 'L':
                number += 50;
                break;
            case 'C':
                if ((i < s.length()-1) && (s[i+1] == 'D' || s[i+1] == 'M')) {
                    number -= 100;
                }
                else {
                    number += 100;
                }
                break;
            case 'D':
                number += 500;
                break;
            default:
                number += 1000;
                break;
        }
    }
    return number;
}

int main(int argc, const char * argv[]) {
    // insert code here...
    std::cout << romanToInt("XIV") << endl;
    return 0;
}
