#include<iostream>
#include<algorithm>
using namespace std;

pair<int, int> weight[101];

int N, M, W, H;
int cache[100][100000];
int dp(int n, int m) {

	if (n == N && m < M) return 10000000;
	if (n == N) return 0;
	int& ret = cache[n][m];
	if (ret != -1) return ret;
	return ret = min(weight[n].second + dp(n + 1, m + weight[n].first), dp(n + 1, m));

}


int main() {
	cin >> N >> M;
	for (int i = 0; i < 100; i++)
		for (int j = 0; j < 100000; j++)
			cache[i][j] = -1;
	int temp = 0;
	for (int i = 0; i < N; i++) {
		cin >> W >> H;
		temp += W;
		weight[i] = { W , H };
	}
	if (temp < M) cout << "ÁË¼ÛÇÕ´Ï´Ù ÇÑ½Â¿± º´Àå´Ô";
	else {
		cout << dp(0, 0);
	}
}