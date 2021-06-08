//
//  main.cpp
//  BinarySearch
//
//  Created by Kaushik Isukapalli on 5/15/21.
//  Copyright © 2021 Kaushik Isukapalli. All rights reserved.
//

#include <iostream>
#include <vector>
using namespace std;

int binarySearch(vector<int> input, int search) {
    int i = 0;
    int j = input.size()-1;
    int m = (i+j)/2;
    while (i < j-1) {
        
        if (input[i] == search) {
            return i;
        }
        else if (input[j] == search) {
            return j;
        }
        else if (input[m] == search) {
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

int main(int argc, const char * argv[]) {
    vector<int> myVector;
    myVector.push_back(1);
    myVector.push_back(4);
    myVector.push_back(8);
    myVector.push_back(10);
    myVector.push_back(17);
    myVector.push_back(25);
    cout << binarySearch(myVector, 17) << endl;;
}
