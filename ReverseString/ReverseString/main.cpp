//
//  main.cpp
//  ReverseString
//
//  Created by Kaushik Isukapalli on 7/21/21.
//  Copyright © 2021 Kaushik Isukapalli. All rights reserved.
//

#include <iostream>
using namespace std;


string reverseVowels(string s) {
    int front = 0;
    int back = s.length()-1;
    while (front < s.length() && s[front] != 'a' && s[front] != 'e' && s[front] != 'i' && s[front] != 'o' && s[front] != 'u') {
        front++;
    }
    while (back >= 0 && s[back] != 'a' && s[back] != 'e' && s[back] != 'i' && s[back] != 'o' && s[back] != 'u') {
        back--;
    }
    while (front <= back) {
        char temp = s[front];
        s[front] = s[back];
        s[back] = temp;
        front++;
        back--;
        while (front < s.length() && s[front] != 'a' && s[front] != 'e' && s[front] != 'i' && s[front] != 'o' && s[front] != 'u') {
            front++;
        }
        while (back >= 0 && s[back] != 'a' && s[back] != 'e' && s[back] != 'i' && s[back] != 'o' && s[back] != 'u') {
            back--;
        }
    }
    return s;
}

bool isHappy(int n) {
    while (n >= 10) {
        int duplicate = n;
        int next = 0;
        while (duplicate > 0) {
            int mod = (duplicate % 10);
            mod *= mod;
            next += mod;
            duplicate /= 10;
        }
        n = next;
    }
    if (n == 1 || n == 7) {
        return true;
    }
    return false;
}

bool isPerfectSquare(int num) {
    int power = 0;
    int duplicate = num;
    while (duplicate >= 10) {
        power++;
        duplicate /= 10;
    }
    int min = 0;
    if (power % 2 == 1) {
        int exp = (power-1)/2;
        min = 10^(2);
    }
    else {
        min = 10^(power/2);
    }
    int max = 10^(min+1);
    for (int i = min; i <= max; i++) {
        if ((i^2) == num) {
            return true;
        }
        else if ((i^2) > num) {
            return false;
        }
    }
    return false;
}

int main(int argc, const char * argv[]) {
    cout << isPerfectSquare(16) << endl;
    return 0;
}
