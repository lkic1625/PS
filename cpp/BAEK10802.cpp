#include<iostream>

using namespace std;

using ull = unsigned long long;
const int MAX = 100'000 + 1;
const int MOD = 20'150'523;

char A[MAX], B[MAX];
int dp[10][MAX], multipleOf3[10][MAX];

int search(int dasd, int asd) {

}

int pow_with_mod(int a, int b, int mod) {
    a = a % mod;
    int ret = 1;
    while (b > 0) {
        if (b % 2 == 1) {
            ret = (ret * a) % mod;
        }
        a = (a * a) % mod;
        b = b / 2;
    }

    return ret;
}

int main() {
    //FAST IO
    ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

    cin >> A;
    cin >> B;

    dp[0][3] = dp[0][6] = dp[0][9] = 1;
    for (int i = 1; i < 10; ++i) {
        for (int j = 1; j < MAX; ++j) {
            if (i == 3 || i == 6 || i == 9) {
                dp[i][j] = pow_with_mod(10, j, MOD);
            } else {
                for (int k = 1; k < 10; ++k) {
                    dp[i][j] += dp[k][j - 1];
                    dp[i][j] %= MOD;
                }
            }
        }
    }

    for (int i = 10; i < 100; ++i) {
        if (i % 3 == 0) {
            multipleOf3[i % 10][1] += 1;
        }
    }
    for (int i = 1; i < 10; ++i) {
        for (int j = 1; j < MAX; ++j) {
            if (i == 3 || i == 6 || i == 9) {
                dp[i][j] = 0;
            } else {
                for (int k = 1; k < 10; ++k) {
                    dp[i][j] += dp[][] dp[k][j - 2];
                    dp[i][j] %= MOD;
                }
            }
        }
    }
}