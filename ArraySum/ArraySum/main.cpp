//
//  main.cpp
//  ArraySum
//
//  Created by Kaushik Isukapalli on 5/19/21.
//  Copyright © 2021 Kaushik Isukapalli. All rights reserved.
//

#include <iostream>
#include <vector>
#include <math.h>
using namespace std;

vector<int> mergeSort(vector<int> &input) {
    if (input.size() <= 1) {
        return input;
    }
    unsigned long m = input.size()/2;
    vector<int> vec1;
    vector<int> vec2;
    for (long i = 0; i < m; i++) {
        vec1.push_back(input[i]);
    }
    for (long j = m; j < input.size(); j++) {
        vec2.push_back(input[j]);
    }
    vec1 = mergeSort(vec1);
    vec2 = mergeSort(vec2);
    input.clear();
    int i = 0;
    int j = 0;
    while (i < vec1.size() || j < vec2.size()) {
        if (i >= vec1.size()) {
            input.push_back(vec2[j]);
            j++;
        }
        else if (j >= vec2.size()){
            input.push_back(vec1[i]);
            i++;
        }
        else if (vec1[i] < vec2[j]) {
            input.push_back(vec1[i]);
            i++;
        }
        else {
            input.push_back(vec2[j]);
            j++;
        }
    }
    return input;
}

int binarySearch(vector<int> &input, int start, int search) {
    int i = start;
    int j = input.size() - 1;
    int m = (i+j)/2;
    if (input[i] == search) {
        return i;
    }
    else if (input[j] == search) {
        return j;
    }
    while (i < j-1) {
        if (input[i] == search) {
            return i;
        }
        else if (input[j] == search) {
            return j;
        }
        if (input[m] == search) {
            return m;
        }
        if (search < input[m]) {
            j = m;
        }
        else {
            i = m;
        }
        m = (i+j)/2;
    }
    return -1;
}

bool arraySum(vector<int> &input, int sum) {
    input = mergeSort(input);
    for (int i = 0; i < input.size()-1; i++) {
        int index = binarySearch(input, i, sum-input[i]);
        if (index >= 0) {
            return true;
        }
    }
    return false;
}

int main(int argc, const char * argv[]) {
//    vector<int> list;
//    list.push_back(3);
//    list.push_back(2);
//    list.push_back(4);
//    list.push_back(10);
//    list.push_back(37);
//    list.push_back(5);
//    list.push_back(2);
//    list.push_back(100);
//    list.push_back(-50);
//    list.push_back(10);
//    bool i = arraySum(list, 137);
//    cout << i << endl;
    string s = "hello";
    s[3] = 'r';
    cout << to_string(-123) << endl;
    
    return 0;
}
