//
//You are given a string s and an integer k. You can choose any character of the string and change it to any other uppercase English character. You can perform this operation at most k times.
//
//Return the length of the longest substring containing the same letter you can get after performing the above operations.
//
//
#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

struct Node {
    int point;
    int head;
    int tail;
};

vector<Node> nodes[28];

class Solution {
public:

    int characterReplacement(string s, int k) {
        for (auto & item: nodes) {
            item.clear();
        }

        int ans = 0;
        int counter = 1;
        int stringSize = s.size();
        for (int i = 1; i < stringSize; ++i) {
            if (s[i] == s[i - 1]) {
                counter += 1;
            } else {
                nodes[s[i - 1] - 'A'].push_back({counter, i - counter, i - 1});
                counter = 1;
            }

            if (i == s.length() - 1) {
                nodes[s[i] - 'A'].push_back({counter, i - counter + 1, i});
            }

            if (counter + k <= stringSize) {
                ans = max(ans, counter + k);
            }
        }

        // boxing
        for (auto & node : nodes) if (!node.empty()) {
            node.push_back({0, stringSize, 0});
        }

        for (auto & node : nodes) if (!node.empty()) {
            int size = node.size(), left = 0, right = left, limit = k, point = node[left].point;
            while (right < size - 1) {
                // sliding window
                do {
                    ++right;
                    int rDiff = node[right].head - node[right - 1].tail - 1;
                    limit -= rDiff;

                    if (limit < 0) {
                        left += 1;
                        int lDiff = (node[left + 1].head - node[left].tail - 1);
                        limit += lDiff;
                        point -= lDiff + node[left].point;
                        continue;
                    } else {
                        point += (node[right].point + rDiff);
                        ans = max(point, ans);
                    }
                } while (left != right && right < size - 1);

                left += 1;
                right = left;
                limit = k;
                point = node[left].point;
            }
        }

        return ans;
    }
};

int main() {
    Solution s = Solution();
    cout << s.characterReplacement("ABCDE", 1);
}
