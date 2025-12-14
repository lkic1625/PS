#include<iostream>

using namespace std;

const int MAX = 1000001;
int root[MAX];
int n, m, type, a, b;

int find(int a) {
	if (root[a] == a) return a;
	return root[a] = find(root[a]);
}

void Union(int a, int b) {
	a = find(a);
	b = find(b);
	root[a] = b;
}

int main() {
	for (int i = 0; i < MAX; i++)
		root[i] = i;
	scanf("%d %d", &n, &m);
	for (int i = 0; i < m; i++) {
		scanf("%d %d %d", &type, &a, &b);
		if (type) printf("%s\n", find(a) == find(b) ? "YES" : "NO");
		else Union(a, b);
	}
}
