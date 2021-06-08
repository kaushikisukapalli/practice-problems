//
//  main.cpp
//  ReverseInt
//
//  Created by Kaushik Isukapalli on 5/20/21.
//  Copyright © 2021 Kaushik Isukapalli. All rights reserved.
//

#include <iostream>
#include <math.h>
using namespace std;

int reverseInt(int x) {
    bool negative = (x < 0);
    string input = to_string(x);
    if (negative) {
        input.erase(input.begin());
    }
    for (unsigned i = 0; i < input.length()/2; i++) {
        char temp = input[i];
        input[i] = input[input.length()-i-1];
        input[input.length()-i-1] = temp;
    }
    while (input[0] == '0' && input.length() > 1) {
        input.erase(input.begin());
    }
    int output = 0;
    try {
        output = stoi(input);
    }
    catch (out_of_range &error) {
        return 0;
    }
    if (negative) {
        output *= -1;
    }
    return output;
}

int main(int argc, const char * argv[]) {
    string a = "";
    a += '5';
    cout << reverseInt(34758) << endl;
    return 0;
}
