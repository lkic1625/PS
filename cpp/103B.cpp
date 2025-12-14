#include<iostream>
#include<set>
using namespace std;

int n, m, x ,y, cycle;
int p[101];
set<int> s;

int find(int x) {
	if (p[x] == x) return x;
	else return p[x] = find(p[x]);
}
void Union(int x, int y) {
	x = find(x);
	y = find(y);
	p[y] = x;
}

int main() {
	scanf("%d %d", &n, &m);
	for (int i = 0; i < 101; i++)
		p[i] = i;
	for (int i = 0; i < m; i++) {
		scanf("%d %d", &x, &y);
		if (find(x) != find(y))
			Union(x, y);
	}
	for (int i = 1; i <= n; i++) {
		s.insert(find(i));
	}
	cout << (s.size() == 1 && n == m ? "FHTAGN!" : "NO") << endl;
	
}