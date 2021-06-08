//
//  main.cpp
//  WordDistance
//
//  Created by Kaushik Isukapalli on 5/14/21.
//  Copyright © 2021 Kaushik Isukapalli. All rights reserved.
//

#include <iostream>
//#include <string>
#include <vector>
#include <cmath>

using namespace std;

class SentenceDistanceFinder {

public:
    SentenceDistanceFinder(vector<string> words) {
        myWords = words;
    }
    int distance(string wordOne, string wordTwo) {
        vector<int> wordsOne;
        vector<int> wordsTwo;
        for (int i = 0; i < myWords.size(); i++) {
            if (myWords[i].compare(wordOne) == 0) {
                wordsOne.push_back(i);
            }
            else if (myWords[i].compare(wordTwo) == 0){
                wordsTwo.push_back(i);
            }
        }
        int minDiff = abs(wordsOne[0]-wordsTwo[0]);
        int i = 0;
        int j = 0;
        while (i < wordsOne.size() && j < wordsTwo.size()) {
            if (minDiff == 1) {
                return 1;
            }
            else if (wordsOne[i] < wordsTwo[j]) {
                i++;
            }
            else {
                j++;
            }
            minDiff = abs(wordsOne[i]-wordsTwo[j]);
        }
        return minDiff;
    }
private:
    vector<string> myWords;
};

int main(int argc, const char * argv[]) {
    vector<string> input;
    input.push_back("the");
    input.push_back("quick");
    input.push_back("brown");
    input.push_back("fox");
    input.push_back("quick");
    SentenceDistanceFinder finder(input);
    cout << finder.distance("the", "fox") << endl;
    cout << finder.distance("quick", "fox") << endl;
    cout << finder.distance("brown", "the") << endl;
    return 0;
}
