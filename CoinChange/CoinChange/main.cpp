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
    for (int j = 0; j < matrix[0].size()-1; j++) {
        output.push_back(matrix[0][j]);
    }
    int vloc = 0;
    int hloc = matrix[0].size()-1;
    int vert = matrix.size()-1;
    int hor = (matrix[0].size()-1) * (-1);
    int vinc = 1;
    int hinc = -1;
    while (vert != 0 && hor != 0) {
        for (int i = vloc; vert != 0 && hor != 0 && i != vloc+vert; i += vinc) {
            output.push_back(matrix[i][hloc]);
        }
        if (vert != 0 && hor != 0) {
            vloc += vert;
            if (vert > 0) {
                vert--;
            }
            else if (vert < 0) {
                vert++;
            }
            vert *= -1;
            vinc *= -1;
        }
        for (int j = hloc; vert != 0 && hor != 0 && j != hloc+hor; j += hinc) {
            output.push_back(matrix[vloc][j]);
        }
        if (vert != 0 && hor != 0) {
            hloc += hor;
            if (hor > 0) {
                hor--;
            }
            else if (hor < 0) {
                hor++;
            }
            hor *= -1;
            hinc *= -1;
        }
    }
    if (vert == 0) {
        for (int j = hloc; j != hloc+hor; j += hinc) {
            output.push_back(matrix[vloc][j]);
        }
        hloc += hor;
    }
    else {
        for (int i = vloc; i != vloc+vert; i += vinc) {
            output.push_back(matrix[i][hloc]);
        }
        vloc += vert;
    }
    output.push_back(matrix[vloc][hloc]);
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
