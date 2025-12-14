#include <iostream>

using namespace std;

const int MAX = 10'000 + 5;
int t, n, a[MAX];
int dp[MAX];


int main() {
    //FAST I/O
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);
    //input
    cin >> t;
    while(t-- > 0){
        cin >> n;
        for(int i = 0; i < n; i++){
            cin >> a[i];
        }
    }
}