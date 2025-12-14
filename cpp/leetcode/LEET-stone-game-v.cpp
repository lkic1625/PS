#include<vector>
#include<iostream>

using namespace std;


class Solution {
public:
    int stoneGameV(vector<int>& stoneValue) {
        int len = stoneValue.size();
        int dp[501][501] = {};
        int subsetSum[501] = {stoneValue[0], };
        for (int i = 1; i < len; ++i) {
            subsetSum[i] += subsetSum[i - 1] + stoneValue[i];
        }

        for (int diff = 1; diff < len; ++diff) {
            for (int left = 0, right = left + diff; left < len && right < len; ++left, ++right) {
                if (left + 1 == right) {
                    dp[left][right] = min(stoneValue[left], stoneValue[right]);
                    continue;
                }

                for (int pivot = left; pivot < right; ++pivot) {
                    int lv = subsetSum[pivot] - subsetSum[left] + stoneValue[left];
                    int rv = subsetSum[right] - subsetSum[pivot + 1] + stoneValue[pivot + 1];

                    if (lv < rv) {
                        dp[left][right] = max(dp[left][right], lv + dp[left][pivot]);
                    } else if(lv > rv) {
                        dp[left][right] = max(dp[left][right], rv + dp[pivot + 1][right]);
                    } else {
                        dp[left][right] = max(
                                dp[left][right],
                                max(dp[left][pivot], dp[pivot + 1][right]) + lv
                        );
                    }
                }
            }
        }

        return dp[0][len - 1];
    }
};

int main() {
    Solution s;
    vector<int> v = {6, 2, 3, 4, 5, 5};
    cout << s.stoneGameV(v) << endl;
}
