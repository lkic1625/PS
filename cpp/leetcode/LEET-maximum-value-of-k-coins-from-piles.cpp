#include <iostream>
#include <vector>

using namespace std;

int cache[1001][2001];

int dp(int k, int index, vector<vector<int>>& piles) {
    if (index == piles.size() && k < 0) {
        return -100000000;
    }

    if (k == 0 || index == piles.size() ) {
        return 0;
    }

    if (cache[k][index] != -1) {
        return cache[k][index];
    }

    int sum = 0;
    cache[k][index] = max(dp(k, index + 1, piles) + sum, cache[k][index]);
    for (int i = 0; i < k && i < piles[index].size(); ++i) {
        sum += piles[index][i];
        cache[k][index] = max(dp(k - (i + 1), index + 1, piles) + sum, cache[k][index]);
    }

    return cache[k][index];
}

class Solution {
public:
    int maxValueOfCoins(vector<vector<int>>& piles, int k) {
        for (int i = 0; i < 2001; ++i) {
            for (int j = 0; j < 2001; ++j) {
                cache[i][j] = -1;
            }
        }

        return dp(k, 0, piles);
    }
};