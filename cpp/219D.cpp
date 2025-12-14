#include<iostream>
#include<vector>
#include<set>
#include<algorithm>
using namespace std;

int cache[200001];
vector<int> parent[200001], child[200001], ans;//adjacency list, ans
int n, s, t;//input variable

int search(int s, int t) {//brute force
	
	int ret = 0;

	for (int i = 0; i < parent[t].size(); i++) {
		if (parent[t][i] != s) {
			ret += 1 + search(t, parent[t][i]);
		}
	}
	for (int i = 0; i < child[t].size(); i++) {
		if (child[t][i] != s) {
			ret += search(t, child[t][i]);
		}
	}

	return ret;
	
}

void dp(int s, int t)//memoization
{
	for (int i = 0; i < parent[t].size(); i++) {
		if (parent[t][i] != s) {
			cache[parent[t][i]] = cache[t] - 1;
			dp(t, parent[t][i]);
		}
	}
	for (int i = 0; i < child[t].size(); i++) {
		if (child[t][i] != s) {
			cache[child[t][i]] = cache[t] + 1;
			dp(t, child[t][i]);
		}
	}
}

int main() {
	//input
	cin >> n;
	for (int i = 0; i < n - 1; i++) {
		scanf("%d %d", &s, &t);
		child[s].push_back(t);
		parent[t].push_back(s);
	}
	
	cache[1] = search(0, 1);
	dp(0, 1);

	int m = 1000000;
	for (int i = 1; i < n + 1; i++) {
		if (cache[i] < m) {
			ans.clear();
			m = cache[i];
		}
		if (cache[i] == m)
			ans.push_back(i);
	}
	//output
	cout << m << endl;
	for (int i = 0; i < ans.size(); i++) {
		printf("%d ", ans[i]);
	}

	return 0;

}