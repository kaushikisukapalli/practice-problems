//
//  main.cpp
//  MergeSortedArray
//
//  Created by Kaushik Isukapalli on 6/4/21.
//  Copyright © 2021 Kaushik Isukapalli. All rights reserved.
//

#include <iostream>
#include <vector>
using namespace std;

void vectorMerge(vector<int>& nums1, int m, vector<int>& nums2, int n) {
    int i = 0;
    int j = 0;
    int s = 0;
    while (i < m+s || j < n) {
        if (i < m+s && j < n && (nums1[i] < nums2[j])) {
            i++;
        }
        else if (i < m+s && j < n) {
            nums1.insert(nums1.begin() + i, nums2[j]);
            j++;
            i++;
            s++;
        }
        else if (i < m+s) {
            i++;
        }
        else {
            nums1.insert(nums1.begin() + i, nums2[j]);
            j++;
            s++;
        }
    }
    for (int s = 0; s < n; s++) {
        nums1.pop_back();
    }
}

int main(int argc, const char * argv[]) {
    vector<int> nums1;
    vector<int> nums2;
    nums1.clear();
    nums2.clear();
    nums1.push_back(1);
    nums1.push_back(2);
    nums1.push_back(3);
    nums1.push_back(0);
    nums1.push_back(0);
    nums1.push_back(0);
    nums2.push_back(2);
    nums2.push_back(5);
    nums2.push_back(6);
    vectorMerge(nums1, 3, nums2, 3);
    for (int i = 0; i < nums1.size(); i++) {
        cout << nums1[i] << " ";
    }
    cout << endl;
    return 0;
}
