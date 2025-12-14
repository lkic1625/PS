#include<iostream>
#include<algorithm>
#include<queue>
#include<set>
using namespace std;

int n, m, node[100001], parent[100001], child[100001] ,x, y;
int cache[100001];
queue<int> v[100001];

bool dfs(int stack, int n ) {
	if (stack == m + 1) return false;
	if (n == 0) return true;

	if (node[n]) 
		return dfs(stack + 1, parent[n]);
	else
		return dfs(0, parent[n]);
	
}

int setTree(int i, int stack) {
	if (stack == m && node[i]) return false;
	
	int ret = 0;
	bool retFlag = true;
	while (v[i].size() != 0) {
		int n = v[i].front();
		v[i].pop();
		if (parent[n] == 0 && n != 1) {
			retFlag = false;
			parent[n] = i;
			int nextStack = node[i] == 1 ? stack + 1 : 0;		
			ret += setTree(n, nextStack);
		}
	}
	return retFlag ? 1 : ret;
}

int main() {
	cin >> n >> m;
	for (int i = 0; i < n; i++) {
		cin >> node[i + 1];
	}
	
	for (int i = 0; i < n - 1; i++) {
		cin >> x >> y;
		v[x].push(y);
		v[y].push(x);
	}
	
	cout << setTree(1, 0);
}

