#include<iostream>
#define MAX 51
using namespace std;


bool e[51][51];
int n, m, T;
int x, y;

int dfs(int x, int y, int z) {
	return e[x][y] && e[y][z] && e[z][x];
}

int main() {
	cin >> T;
	int test_case = T;
	while (T-- > 0) {
		cin >> n >> m;
		int ans = 0;
		for (int i = 0; i < MAX; i++)
			for (int j = 0; j < MAX; j++)
				e[i][j] = 0;

		for (int i = 0; i < m; i++) {
			cin >> x >> y;
			e[x][y] = 1;
			e[y][x] = 1;
		}
		for (int i = 1; i <= n; i++) {
			for (int j = i + 1; j <= n; j++) {
				for (int k = j + 1; k <= n; k++) {
					ans += dfs(i, j, k);
				}
			}
		}
		cout << "#" << test_case - T << " " << ans;
	}
}