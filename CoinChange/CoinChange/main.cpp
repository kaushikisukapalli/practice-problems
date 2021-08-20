//
//  main.cpp
//  CoinChange
//
//  Created by Kaushik Isukapalli on 8/2/21.
//  Copyright © 2021 Kaushik Isukapalli. All rights reserved.
//

#include <iostream>
#include <vector>
using namespace std;

vector<int> spiralOrder(vector<vector<int>>& matrix) {
    vector<int> output;
    int hlength = matrix[0].size()-1;
    int vlength = matrix.size()-1;
    for (int j = 0; j < matrix[0].size()-1; j++) {
        output.push_back(matrix[0][j]);
    }
    int vstart = 0;
    int hstart = matrix[0].size()-1;
    while (hlength > 0 || vlength > 0) {
        for (int i = vstart; i < vstart+vlength; i++) {
            output.push_back(matrix[i][hstart]);
        }
        vstart += vlength;
        vlength--;
        for (int j = hstart; j > hstart-hlength; j--) {
            output.push_back(matrix[vstart][j]);
        }
        hstart -= hlength;
        hlength--;
        for (int i = vstart; i > vstart-vlength; i--) {
            output.push_back(matrix[i][hstart]);
        }
        vstart -= vlength;
        vlength--;
        for (int j = hstart; j < hstart+hlength; j++) {
            output.push_back(matrix[vstart][j]);
        }
        hstart += hlength;
        hlength--;
    }
    output.push_back(matrix[vstart][hstart]);
    return output;
}

int main(int argc, const char * argv[]) {
    vector<vector<int>> mat;
    vector<int> row1;
    row1.push_back(1);
    row1.push_back(2);
    row1.push_back(3);
    vector<int> row2;
    row2.push_back(4);
    row2.push_back(5);
    row2.push_back(6);
    vector<int> row3;
    row3.push_back(7);
    row3.push_back(8);
    row3.push_back(9);
    mat.push_back(row1);
    mat.push_back(row2);
    mat.push_back(row3);
    vector<int> output = spiralOrder(mat);
    for (int i = 0; i < output.size(); i++) {
        cout << output[i] << endl;
    }
    return 0;
}
