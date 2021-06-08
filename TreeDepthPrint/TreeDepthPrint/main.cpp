//
//  main.cpp
//  TreeDepthPrint
//
//  Created by Kaushik Isukapalli on 5/16/21.
//  Copyright © 2021 Kaushik Isukapalli. All rights reserved.
//

#include <iostream>
#include <vector>
using namespace std;

struct Node {
    int value;
    Node *left = nullptr;
    Node *right = nullptr;
//    Node *parent;
    //bool isLeft;
    int depth;
};

vector<Node*> nodes;

void printDepthRecursive(Node *root, int depth) {
    if (!root) {
        return;
    }
    root->depth = depth;
    nodes.push_back(root);
    printDepthRecursive(root->left, depth+1);
    printDepthRecursive(root->right, depth+1);
}

void printDepth(Node *root) {
    printDepthRecursive(root, 1);
    cout << nodes[0]->value << endl;
    int maxDepth = 1;
    for (int i = 1; i < nodes.size(); i++) {
        if (nodes[i]->depth > maxDepth) {
            maxDepth = nodes[i]->depth;
        }
    }
    int currentDepth = 2;
    while (currentDepth <= maxDepth) {
        for (int i = 1; i < nodes.size(); i++) {
            if (nodes[i]->depth == currentDepth) {
                cout << nodes[i]->value << " ";
            }
        }
        cout << endl;
        currentDepth++;
    }
}

int main(int argc, const char * argv[]) {
    Node input;
    input.value = 5;
    Node inputLeft;
    inputLeft.value = 6;
    input.left = &inputLeft;
    Node inputRight;
    inputRight.value = 4;
    input.right = &inputRight;
    Node ll;
    ll.value = 7;
    inputLeft.left = &ll;
    Node rl;
    rl.value = 3;
    inputRight.left = &rl;
    Node rr;
    rr.value = 8;
    inputRight.right = &rr;
    printDepth(&input);
    return 0;
}
