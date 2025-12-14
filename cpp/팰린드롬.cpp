#include<iostream>

using namespace std;

int cache[2001][2001], N, S, E, M, num[2001];


int main() {
	cin >> N;
	for (int i = 0; i < N; i++) {
		cin >> num[i];
	}

	for (int j = 0; j < N; j++) {
		for (int i = 0; i + j < N; i++) {
			int flag = num[i] == num[i + j];
			if (j > 1) cache[i][i + j] = flag && cache[i + 1][i + j - 1];
			else cache[i][i + j] = flag;	
		}	
	}
	
	cin >> M;
	for (int i = 0; i < M; i++) {
		scanf("%d %d", &S, &E);
		printf("%d\n", cache[S - 1][E - 1]);
	}
}