#include<iostream>
#include<vector>
using namespace std;

const int MAX_SIZE = 1000001;
int root[MAX_SIZE];
int M1 = 1, M2 = 2;
int s[MAX_SIZE], N, M, I, J, T;
vector<int> adj[MAX_SIZE];
long long K;
/* find(x): Àç±Í ÀÌ¿ë */
int find(int x) {
	if (root[x] == x) {
		return x;
	}
	else {
		return root[x] = find(root[x]);
	}
}

void Union(int x, int y) {
	x = find(x);
	y = find(y);
	if (s[x] > s[y]) {
		root[x] = y;
	}
	else {
		root[y] = x;
	}
}

int main() {

	for (int i = 0; i < MAX_SIZE; i++) {
		root[i] = i;
	}
	cin >> N >> M >> K;
	for (int i = 1; i <= N; i++) {
		cin >> s[i];
	}
	for (int i = 0; i < M; i++) {
		cin >> I >> J;
		adj[I].push_back(J);
		adj[J].push_back(I);
	}
	for (int i = 1; i <= N; i++) {
		for (auto iter : adj[i]) {
			if ((i + 1 + N) % N == iter || (i - 1 + N) % N == iter) {

			}
			else {
				
			}
		}
	}
	for (int i = 1; i <= N; i++) {
		find(i);
		if (root[i] == i)
			K -= s[i];
	}
	cout << (K < 0 ? "NO" : "YES");

}