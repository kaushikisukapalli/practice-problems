//
//  main.cpp
//  ContainsDuplicate
//
//  Created by Kaushik Isukapalli on 6/18/21.
//  Copyright © 2021 Kaushik Isukapalli. All rights reserved.
//

#include <iostream>
#include <vector>
using namespace std;

vector<int> combine(vector<int>& left, vector<int>& right) {
    int i = 0;
    int j = 0;
    vector<int> output;
    output.clear();
    while (i < left.size() && j < right.size()) {
        if (left[i] < right[j]) {
            output.push_back(left[i]);
            i++;
        }
        else {
            output.push_back(right[j]);
            j++;
        }
    }
    if (j >= right.size()) {
        while (i < left.size()) {
            output.push_back(left[i]);
            i++;
        }
    }
    else if (i >= left.size()) {
        while (j < right.size()) {
            output.push_back(right[j]);
            j++;
        }
    }
    return output;
}

vector<int> mergeSort(vector<int>& input) {
    if (input.size() <= 1) {
        return input;
    }
    vector<int> left;
    vector<int> right;
    left.clear();
    right.clear();
    for (int i = 0; i < input.size()/2; i++) {
        left.push_back(input[i]);
    }
    for (int i = input.size()/2; i < input.size(); i++) {
        right.push_back(input[i]);
    }
    left = mergeSort(left);
    right = mergeSort(right);
    return combine(left, right);
}

bool containsDuplicate(vector<int>& nums) {
    nums = mergeSort(nums);
    for (int i = 0; i < nums.size()-1; i++) {
        if (nums[i] == nums[i+1]) {
            return true;
        }
    }
    return false;
}


int main(int argc, const char * argv[]) {
    vector<int> test;
    test.clear();
    test.push_back(1);
    test.push_back(2);
    test.push_back(3);
//    test.push_back(1);
    cout << containsDuplicate(test) << endl;
    std::cout << "Hello, World!\n";
    return 0;
}
