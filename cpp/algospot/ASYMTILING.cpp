	//algospot ASYMTILING
#include<iostream>
#include<string.h>
#define MOD 1000000007
using namespace std;

int cache[101];
int C;
int n;
int TILING(int n);
int TILING2(int n);
int main() {

	cin >> C;
	while (C-- > 0) {
		memset(cache, -1, sizeof(cache));
		cin >> n;
		cout << TILING2(n) % MOD << endl;
	}
}


int TILING(int n ) {
	if (n <= 1) return 1;
	
	int& ret = cache[n];
	if (ret != -1) return ret;
	return ret = (TILING(n - 1) + TILING(n - 2)) % MOD;
}

int TILING2(int n) {
	if (n % 2) return (TILING(n) - TILING(n/2) + MOD);
	return (TILING(n) - (TILING(n / 2) + TILING(n / 2 - 1)) % MOD + MOD);
	
}