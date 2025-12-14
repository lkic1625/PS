#include<iostream>
#include<algorithm>
#include<string.h>
using namespace std;

int C, n, m;
int N[100], M[100];
int cache[101][101];
int join(int m_pos, int n_pos);
int main() {

	cin >> C;
	while (C-- > 0) {
		cin >> n >> m;

		memset(cache, -1, sizeof(cache));
		for (int i = 0; i < n; i++) {
			cin >> N[i];
		}
		for (int i = 0; i < m; i++) {
			cin >> M[i];
		}
		cout << join(-1, -1) - 2 << endl;
	}
}
int join(int n_pos, int m_pos) {

	int& ret = cache[n_pos + 1][m_pos + 1];
	if (ret != -1) return ret;

	int a = (n_pos == -1) ? -1 : N[n_pos];
	int b = (m_pos == - 1) ? -1 : M[m_pos];

	int cmp = max(a, b);

	ret = 2;
	for (int i = n_pos + 1; i < n; i++) {
		if (cmp < N[i])
			ret = max(ret, join(i, m_pos) + 1);
	}
	for (int i = m_pos + 1; i < m; i++) {
		if (cmp < M[i])
			ret = max(ret, join(n_pos, i) + 1);
	}

	return ret;
}