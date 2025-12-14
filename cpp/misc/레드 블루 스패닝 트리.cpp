#include<iostream>
#include<vector>
using namespace std;

struct Edge {
	int from, to, cost;
	Edge(int from, int to, int cost) : from(from), to(to), cost(cost) {};
	Edge() {};
};
int root[1001];
int n, m, k, f, t, tmp1, tmp2;
char c;
vector<Edge> s;
int find(int a) {
	if (root[a] == a) return a;
	return root[a] = find(root[a]);
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0);
	do {
		cin >> n, m, k;
		for (int i = 0; i < 1001; i++) root[i] = i;
		for (int i = 0; i < m; i++) {
			cin >> c >> f >> t;
			s.push_back(Edge(f, t, c == 'B' ? 0 : 1));
		}
		for (auto iter = s.rbegin(); iter != s.rend(); iter++) {
			auto edge = *iter;
			int fR = find(edge.from);
			int tR = find(edge.to);
			if (fR != tR){
				root[fR] = tR;
			}
				
		}

	} while (n != 0 && m != 0 && k != 0);
	
}