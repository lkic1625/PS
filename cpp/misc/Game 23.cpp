//https://codeforces.com/contest/1141/problem/A
#include<iostream>

using namespace std;

int is23(int q) {
	if (q == 1) return 0;
	if(q % 2 == 0)	return is23(q/2) + 1;
	if (q % 3 == 0)	return is23(q / 3) + 1;
	else return -1000;
}

int n, m;

int main() {
	cin >> n >> m;
	int q = is23(m / n);
	if(m % n == 0) cout << (q < 0 ? -1 : q) << endl;
	else cout << -1 << endl;
}