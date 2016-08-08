//
//  knapsack.cpp
//  HappyCoding
//
//  Created by Guan Wang on 8/8/16.
//  Copyright © 2016 Hellocomrade. All rights reserved.
//
#include <vector>
#include <algorithm>
#include <cassert>
using namespace std;
class SolutionKnapsack {
public:
    int Knapsack01(const vector<int>& values, const vector<int>& weights, int capacity) {
        unsigned long len = values.size();
        if(weights.size() != len)return -1;
        else if(len == 0)return 0;
        vector<vector<int> > memo(len, vector<int>(capacity, 0));
        for(int j = 1; j <= capacity; ++j)
            if(weights[0] <= j)memo[0][j - 1] = values[0];
        for(int i = 0; i < len; ++i)
            if(weights[i] <= 1)memo[i][0] = values[i];
        for(int i = 1; i < len; ++i) {
            for(int j = 1; j <= capacity; ++j) {
                if(weights[i] >= j)memo[i][j - 1] = std::max(values[i], memo[i - 1][j - 1]);
                else
                    memo[i][j - 1] = std::max(values[i] + memo[i - 1][j - weights[i] - 1], memo[i - 1][j - 1]);
            }
        }
        return memo[len - 1][capacity - 1];
    }
};
void TestKnapsack() {
    SolutionKnapsack so;
    assert(220 == so.Knapsack01(vector<int>{60, 100, 120}, vector<int>{10, 20, 30}, 50));
}
