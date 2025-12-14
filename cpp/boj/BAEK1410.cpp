//
// Created by 조원빈 on 2022/04/15.
//

#include <iostream>
#include <vector>
#include <string>

using ull = unsigned long long;

using namespace std;

const int MOD = 1'000'003;
const int MAX_LEN = 50;
const int MAX_N = 15;
const int MAX_K = MAX_N;
const char WILD_CARD = '?';

ull N, K;
ull dp[MAX_LEN][100000];
string patterns[MAX_N + 1];
vector<ull> target;

int main() {
    //fast I/O
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    cin >> N >> K;
    for (int i = 0; i < N; ++i) {
        cin >> patterns[i];
    }

    int limit = (1 << N);
    int size = patterns[0].length();
    for (int i = 0; i < size; ++i) {
            for (char alp = 'a'; alp <= 'z'; ++alp) {
                int groups = 0;
                for (int j = 0; j < N; ++j) {
                    if (patterns[j][i] == alp || patterns[j][i] == WILD_CARD) {
                        groups |= (1 << j);
                    }
                }
                if (i == 0) {
                    ++dp[i][groups];
                } else {
                    for (int j = 1; j < limit; ++j) {
                        dp[i][j & groups] += dp[i - 1][j];
                        dp[i][j & groups] %= MOD;
                    }
                }
            }
    }

    ull ans = 0;
    for (int bit = 0; bit < limit; ++bit) {
        if (__builtin_popcount(bit) == K) {
            ans += dp[size - 1][bit];
            ans %= MOD;
        }
    }
    cout << ans % MOD;
}