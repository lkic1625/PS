#include<iostream>
#include<string.h>
#include<vector>
#include<algorithm>
using namespace std;

const long long MOD = 20091101;

int T, N, K, D[100001], psum[100001], cache[100010], pos[100010];
vector<int> ways[100010];

int main() {

	cin >> T;
	while (T-- > 0) {
		//input phase
		cin >> N >> K;
		for (int i = 0; i <= N; i++) ways[i].clear();
		for (int i = 1; i <= N; i++) {
			scanf("%d", &D[i]);
			psum[i] = (D[i] % K) + (psum[i - 1] % K);
			psum[i] %= K;
			ways[psum[i]].push_back(i);
			pos[i] = ways[psum[i]].size();
		}
		//init phase
		memset(cache, -1, sizeof(cache));
		for (int i = 0; i < K; i++) ways[i].push_back(N + 3);

		long long ans = 0;
		for (int i = 0; i < K; i++) {
			long long param = (ways[i].size() - 1);
			ans = (ans + (((param) * (param - 1) / 2))) % MOD;

		}
		cache[N] = D[N] % K == 0;
		for (int cur = N - 1; cur > 0; cur--) {
			int next = ways[psum[cur]][pos[cur]];
			cache[cur] = max(cache[cur + 1] + (D[cur] % K == 0), 1 + cache[next + 1]);
		}	
		cout << ans + (psum[N] % K == 0)<< " " << cache[1] + (psum[N] % K == 0) << endl;
	}
}