#include<iostream>
#include<queue>
#include<algorithm>

using namespace std;

int n, a, b;
int e[1001][1001];
int root[1001];
queue<pair<int, int>> road;

int find(int x) {
	if (x == root[x]) return x;
	return root[x] = find(root[x]);
}

void _union(int x, int y) {
	// 각 원소가 속한 트리의 루트 노드를 찾는다.
	x = find(x);
	y = find(y);

	root[y] = x;
}

int main() {

	for (int i = 0; i < 1001; i++)
		root[i] = i;
	cin >> n;

	for (int i = 0; i < n - 1; i++) {
		cin >> a >> b;
		if (find(a) == find(b)) {
			road.push(make_pair(a, b));
		}
		else {
			int s = max(a, b), t = min(a, b);
			_union(s, t);
		}
	}
	int p = -1;
	cout << road.size() << endl;
	for (int i = 1; i <= n; i++) {
		
		if (root[i] == i) {
			if (p == -1) p = i;
			else {
				pair<int, int> temp = road.front();
				road.pop();
				printf("%d %d %d %d\n", temp.first, temp.second, p ,i);
			}
		}
		
	}
	




}