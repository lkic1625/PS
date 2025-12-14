#include<iostream>

using namespace std;

long long N, input, map[111][111];

int main() {
	cin >> N;
	map[1][1] = 1;
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++) {
			cin >> input;
			if (input == 0) continue;
			map[i + input][j] += map[i][j];
			map[i][j + input] += map[i][j];
		}
	}
	cout << map[N][N];
	
	
	
}