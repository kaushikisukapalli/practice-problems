//
//  main.cpp
//  MergeSort
//
//  Created by Kaushik Isukapalli on 7/15/21.
//  Copyright © 2021 Kaushik Isukapalli. All rights reserved.
//

#include <iostream>
#include <vector>
#include <map>
using namespace std;
vector<int> combine(vector<int> &vec1, vector<int> &vec2) {
    vector<int> output;
    output.clear();
    int i = 0;
    int j = 0;
    while (i < vec1.size() && j < vec2.size()) {
        if (vec1[i] < vec2[j]) {
            output.push_back(vec1[i]);
            i++;
        }
        else {
            output.push_back(vec2[j]);
            j++;
        }
    }
    while (i < vec1.size()) {
        output.push_back(vec1[i]);
        i++;
    }
    while (j < vec2.size()) {
        output.push_back(vec2[j]);
        j++;
    }
    return output;
}

void mergeSort(vector<int> &input) {
    if (input.size() <= 1) {
        return;
    }
    vector<int> left;
    vector<int> right;
    left.clear();
    right.clear();
    for (int i = 0; i < input.size()/2; i++) {
        left.push_back(input[i]);
    }
    for (int j = input.size()/2; j < input.size(); j++) {
        right.push_back(input[j]);
    }
    mergeSort(left);
    mergeSort(right);
    input = combine(left, right);
}

vector<int> intersection(vector<int>& nums1, vector<int>& nums2) {
    vector<int> output;
    mergeSort(nums1);
    mergeSort(nums2);
    int i = 0;
    int j = 0;
    while (i < nums1.size() && j < nums2.size()) {
        if (nums1[i] == nums2[j]) {
            output.push_back(nums1[i]);
            while (nums1[i] == output[output.size()-1]) {
                i++;
            }
            while (nums2[j] == output[output.size()-1]) {
                j++;
            }
        }
        else if (nums1[i] < nums2[j]) {
            i++;
        }
        else {
            j++;
        }
    }
    return output;
}

int main(int argc, const char * argv[]) {
    map<string, char> my;
    cout << ((int) my["sdf"] != 0) << endl;
    return 0;
}
