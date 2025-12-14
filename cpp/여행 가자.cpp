#include<iostream>

using namespace std;

int root[201];
int N, M, temp, temp2;
bool ans = true;

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

	for (int i = 0; i < 200; i++)
		root[i] = i;

	scanf("%d", &N);
	scanf("%d", &M);
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++) {
			scanf("%d", &temp);
			if (temp) Union(i, j);
		}
	}
	scanf("%d", &temp);
	for (int i = 1; i < M; i++) {
		scanf("%d", &temp2);
		ans = ans && (find(temp) == find(temp2));
		temp = temp2;
	}
	cout << (ans ? "YES" : "NO") << endl;


}