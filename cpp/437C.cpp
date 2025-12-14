#include<iostream>
#include<queue>
#include<set>
#include<vector>
using namespace std;

int n, m, x, y, ans;

bool isDestroyed[1001];
int weight[1001];
queue<int> graph[1001];
set<pair<int, int>> s;

void search() {
	for (auto iter = s.rbegin(); iter != s.rend(); iter++) {
		auto pair = *iter;
		int node = pair.second;

		while (graph[node].size() != 0) {

			int vertex = graph[node].front();
			graph[node].pop();

			if (!isDestroyed[vertex]) {
				ans += weight[vertex];
			}
		}
		isDestroyed[node] = true;
	}
}


int main() {
	cin >> n >> m;
	int temp;
	for (int i = 0; i < n; i++) {
		cin >> temp;
		weight[i + 1] = temp;
		s.insert(make_pair(temp, i + 1));
	}
	for (int i = 0; i < m; i++) {
		cin >> x >> y;
		graph[x].push(y);
		graph[y].push(x);
	}
	search();
	cout << ans;
}