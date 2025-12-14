#include<iostream>
#include<vector>
#include<algorithm>
#include<string.h>

using namespace std;

// boundary for NPE(Null pointer exception)
const int MAX = 50 + 5, SUPER_MAX = 10100000;

int N, parent;
int cache[MAX][MAX];

vector<int> adj[MAX];


vector<int> &permutation_generator(int size) {
	vector<int> permutation;
	for(int i = 0; i < size; i++) {
		permutation.push_back(i + 1);
	}
	
	return permutation;
}


int dp(int node, int n) {
	bool amILeaf = adj[node].size() == 0;
	if (amILeaf) {
		return 0;
	}
	
	int& ret = cache[node][n];
	if (ret != -1) {
		return ret;
	}
	
	vector<int> permutation = permutation_generator(adj[node].size());
	
	ret = SUPER_MAX;
	do {
		int maximumDepth = 0;
		for (int order = 1; i <= permutation.size(); order++) {
			maximumDepth = max(maximumDepth, (order) + dp(adj[node][permutation[order]], order))
		}
		
		ret = min(ret, maximumDepth);
	} while(prev_permutation(permutation.begin(), permutation.end()))
	
	return ret;
}

int main() {
	memset(cache, -1, sizeof cache);
	cin >> N;
	for(int i = 0; i < N; i++) {
		cin >> parent;
		if (parent == -1) {
			continue;
		}
		adj[parent].push_back(i);
	}
	
	int ans = 0
	ans = dp(0, 1);
	cout << ans;
	
}