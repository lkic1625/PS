//
// Created by 조원빈 on 2022/04/10.
//

#include<iostream>

using namespace std;

const int MAX_N = 500, MAX_T = 5000;

int t, n, rest_times[MAX_N + 10], results[MAX_N + 10];
int dp[2][MAX_N + 10], visited[2][MAX_N + 10];


int main() {
    // FAST IO
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    cin >> t >> n;
    for (int i = 1; i <= n; i++) {
        cin >> rest_times[i];
    }

    int pivot;
    for (int i = 1; i <= n; i++) {
        pivot = 0;
        for (int j = 0; j < 2; j++) {
            if (visited[j][i]) {
                visited[j][i] = false;
                dp[j][i] = dp[j][i - 1];
            }
            else {
                if (pivot == 0 && dp[j][i - 1] + rest_times[i] <= t) {
                    dp[j][i] = dp[j][i - 1] + rest_times[i];
                    visited[j][i] = true;
                    pivot++;
                }
                else {
                    dp[j][i] = dp[j][i - 1];
                }
            }
        }
        if (pivot == 0) {
            i -= 2;
        }
    }


    for (int i = 0; i < 2; i++) {
        for (int j = 1; j <= n; j++) {
            if (visited[i][j]) {
                results[j] = dp[i][j - 1];
            }
        }
    }

    for (int i = 1; i <= n; i++) {
        cout << results[i] << " ";
    }
}

