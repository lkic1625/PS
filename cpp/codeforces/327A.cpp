/*
A. Flipping Game
https://codeforces.com/problemset/problem/327/A

Input
The first line of the input contains an integer n (1 ≤ n ≤ 100). 
In the second line of the input there are n integers: a 1, a 2, ..., a n. 
It is guaranteed that each of those n values is either 0 or 1.

output
Print an integer — the maximal number of 1s that can be obtained after exactly one move.

*/

#include<iostream>
#include<algorithm>
using namespace std;

const int ELEMENT_MAXIMUM = 100;

int n, a[ELEMENT_MAXIMUM + 1], cache[ELEMENT_MAXIMUM + 1][ELEMENT_MAXIMUM + 1];

int main() {
	//fast I/O
	ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

	int ans = 0;
	int sum = 0;
	//input
	cin >> n;
	for (int i = 0; i < n; i++) {
		cin >> a[i];
		sum += a[i];
	}
	//preprocessing
	for (int i = 0; i < n; i++) {
		cache[i][i] = sum + (a[i] == 0 ? 1 : - 1);
	}
	//dp
	for (int i = 0; i < n; i++) {
		for (int j = i + 1; j < n; j++) {
			cache[i][j] = cache[i][j - 1] + (a[j] == 0 ? 1 : - 1);
		}
	}
	//find maximum value
	for (int i = 0; i < n; i++) {
		for (int j = i; j < n; j++) {
			ans = max(ans, cache[i][j]);
		}
	}
	//output
	cout << ans << endl;
}
