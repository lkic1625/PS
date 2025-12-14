//
// Created by 조원빈 on 2021/08/14.
//

#include<iostream>
#include<algorithm>
#include <vector>

using namespace std;

const int MAX = 1'000'000, INF = 1'000'000'000 + 4;

int A[MAX + 1], position[MAX + 1];
vector<int> LIS;

int N, max_index;

int main () {
    // FAST IO
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    // input
    cin >> N;
    for (int i = 0; i < N; ++i) {
        cin >> A[i];
    }

    LIS.push_back(-INF);
    for (int i = 0; i < N; ++i) {
        if (LIS[max_index] < A[i]) {
            LIS.push_back(A[i]);
            max_index++;
            position[i] = max_index;
        } else {
            int index = lower_bound(LIS.begin(), LIS.end(), A[i]) - LIS.begin();
            LIS[index] = A[i];
            position[i] = index;
        }
    }

    vector<int> reverse_ans = { };
    int next_length = max_index;
    for (int i = N - 1; i >= 0 && next_length > 0; --i) {
        if (position[i] == next_length) {
            --next_length;
            reverse_ans.push_back(A[i]);
        }
    }

    // output
    cout << max_index << endl;
    for (auto iter = reverse_ans.rbegin(); iter < reverse_ans.rend(); iter++) {
        cout << *iter << " ";
    }
}