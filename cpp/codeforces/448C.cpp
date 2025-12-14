//https://codeforces.com/problemset/problem/448/C
//C. Painting Fence

/*
"Input"
The first line contains integer n(1 ≤ n ≤ 5000) — the number of fence planks.
The second line contains n space - separated integers a 1, a 2, ..., a n(1 ≤ a i ≤ 10^9).

"output"
Print a single integer — the minimum number of strokes needed to paint the whole fence.

*/
#include<iostream>
#include<algorithm>
#include<vector>

using namespace std;
const int MAX = 5000;
const int INF = 1.0e9;
int n, fenceHeight[MAX + 1];

int dc(int start, int end) {
	
	//if (end - start <= 1 && fenceHeight[start] > 0) return 1;
	if (end - start == 0) return 0;
	int stroke = 0,
		length = end - start,
		minHeight = INF;

	for (int i = start; i < end; i++) {
		minHeight = min(fenceHeight[i], minHeight);
	}
	stroke = minHeight;

	for (int i = start; i < end; i++) {
		fenceHeight[i] -= minHeight;
	}

	int bifurcation = start;
	for (int i = start; i <= end; i++) {
		if (fenceHeight[i] == 0) {
			stroke += dc(bifurcation, i);
			bifurcation = i + 1;
		}
	}

	return min(stroke, length);
}

int main() {
	//fast I/O
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	//input 
	cin >> n;
	for (int i = 0; i < n; i++) {
		cin >> fenceHeight[i];
	}

	cout << dc(0, n) << "\n";


}