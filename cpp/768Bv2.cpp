/*
B. Code For 1
https://codeforces.com/problemset/problem/768/B

"input"
The first line contains three integers n, l, r (0 ≤ n < 2^50, 0 ≤ r - l ≤ 10^5, r ≥ 1, l ≥ 1) – initial element and the range l to r.
It is guaranteed that r is not greater than the length of the final list.

"output"
Output the total number of 1s in the range l to r in the final sequence.
*/

#include<iostream>

using namespace std;

long long n, l, r, cache[51] = { 1, };

int dp(int n, int l, int r) {

}


int main()
{
	//fast I/O
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	//preprocessing
	for (int i = 1; i < 51; i++) {
		cache[i] = cache[i - 1] * 2;
	}
	
	//input 
	cin >> n >> l >> r;


}