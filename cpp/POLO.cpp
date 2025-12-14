#include<iostream>

using namespace std;

constexpr auto MOD = 10000000;

int cache[101][101];
int n,C;

int polo(int top, int bottom) {
	
	if (bottom == 0) return 1;

	int& ret = cache[top][bottom];
	if (ret != -1) return ret;
	
	int cnt;
	ret = 0;

	for (int i = bottom; i > 0; i--) {
		cnt = top == 0 ? 1 : (i + top - 1);
		ret += (cnt * polo(i, bottom - i)) % MOD;
		ret %= MOD;
	}
	return ret % MOD;	

}

int main() {
	cin >> C;
	while (C-- > 0) {
		for (int i = 0; i < 101; i++)
			for (int j = 0; j < 101; j++)
				cache[i][j] = -1;
		cin >> n;
		cout << polo(0, n) << endl;
	}
}