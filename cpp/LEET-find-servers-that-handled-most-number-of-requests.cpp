#include<iostream>
#include<vector>

using namespace std;

const int MAX_K = 100'000 + 1;
const int NOT_FOUND = -1;


long long seg[2 * MAX_K * 4];
int counter[MAX_K];

void update(int lo, int hi, long long value, int node, int left, int right) {
    if (hi < left || right < lo) {
        return;
    }
    if (lo <= left && right <= hi) {
        seg[node] = min(seg[node], value);
    }
    if (left == right) return;

    int mid = (left + right) / 2;
    update(lo, hi, value, node * 2, left, mid);
    update(lo, hi, value, node * 2 + 1, mid + 1, right);

    seg[node] = min(seg[node * 2], seg[node * 2 + 1]);
}

int query(int lo, int hi, int node, int left, int right, long long threshold) {
    if (hi < left || right < lo) {
        return NOT_FOUND;
    }
    if (seg[node] > threshold) {
        return NOT_FOUND;
    }

    if (left == right) {
        return left;
    }

    int mid = (left + right) / 2;
    int leftChild = query(lo, hi, node * 2, left, mid, threshold);
    if (left == NOT_FOUND) {
        return query(lo, hi, node * 2 + 1, mid + 1, right, threshold);
    }

    return leftChild;
}

class Solution {
public:
    vector<int> busiestServers(int k, vector<int>& arrival, vector<int>& load) {
        // init
        for (int i = 0; i < 2 * k * 4; ++i) {
            seg[i] = 0;
        }

        for (int i = 0; i < k; ++i) {
            counter[i] = 0;
        }

        int len = arrival.size();
        for (int i = 0; i < len; ++i) {
            int targetServer = query(i % k, 2 * k, 1, 1, 2 * k, arrival[i]);
            if (NOT_FOUND == targetServer) {
                continue;
            }
            targetServer %= k;
            counter[targetServer - 1]++;

            update(targetServer, targetServer, arrival[i] + load[i], 1, 1, 2 * k);
            update(targetServer + k, targetServer + k, arrival[i] + load[i], 1, 1, 2 * k);
        }

        int mx = -1;
        for (int i = 0; i < k; ++i) {
            mx = max(counter[i], mx);
        }

        vector<int> ans;
        for (int i = 0; i < k; ++i) {
            if (mx == counter[i]) {
                ans.push_back(i);
            }
        }

        return ans;
    }
};

int main() {
    Solution s = Solution();
    vector<int> arr = {1, 2, 3, 4};
    vector<int> lo = {1, 2, 1, 2};
    for (const auto &item: s.busiestServers(3, arr, lo)) {
        cout << item << " ";
    }
}