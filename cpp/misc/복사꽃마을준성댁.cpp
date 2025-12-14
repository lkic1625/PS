#include<iostream>
#include<vector>

using namespace std;

struct Branch {
	int count;
	vector<int> peach;
	vector<int> child;
};

int cache[50000][3000];
int peach[50000];
Branch branch[3000];
int K, M, N, T, input;

int dfs(int parent, int cur) {
	
	branch[cur].count += branch[cur].peach.size();
	
	for (auto iter : branch[cur].child) {
		if (iter == parent) continue;
		branch[cur].count += dfs(cur, iter);
	}

	return branch[cur].count;
}

int dp(int K, int parent, int cur) {
	return 0;
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);
	
	cin >> T;
	while (T-- > 0) {
		cin >> N >> M >> K;
		for (int i = 0; i < N; i++) {
			cin >> input;
			branch[input].peach.push_back(i);
		}
		for (int i = 0; i < M; i++) {
			if (i == 0) continue;
			cin >> input;
			branch[input].child.push_back(i);
		}
		dfs(-1, 0);

	}



}