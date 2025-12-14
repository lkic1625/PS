#include<iostream>
#define MOD %;

using namespace std;

const int MAX_N = 1'000'000, PRIME = 1'000'000'000 + 7;

int dp[MAX_N + 1], N;
int hanoi[MAX_N + 1];

int main() {
    cin >> N;
    dp[1] = 3;
    hanoi[1] = 1;
    for(int i = 1; i <= N; i++) {
        hanoi[i] = hanoi[i - 1] * 2 + 1;
    }
    for(int i = 1; i <= N; i++) {
        dp[i] = 2 * dp[i - 1] +
    }
}