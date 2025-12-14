#include<iostream>
#include<math.h>
using namespace std;
#define MOD  1000000007

int T, N;
double cache[1000001];

int main() {
	cin >> T;
	int temp = 0;
	cache[1] = 3;
	for (int i = 2; i < 1000001; i++) {
		temp = i - 1;
		cache[i] = (long long)cache[temp] % MOD;
		double temp2 = (4 * temp + 2) / (double)(temp + 2);
		cache[i] *= temp2;
		cache[i] = (long long)cache[i] % MOD;
		cache[i] *= 3;
		cache[i] = (long long)cache[i] % MOD;
		/*	cache[i] %= MOD;
			cache[i] *= ((2 * temp + 2) % MOD);
			cache[i] %= MOD;
			cache[i] /= ((temp + 2));
			cache[i] %= MOD;
			cache[i] /= ((temp + 1));
			cache[i] %= MOD;*/
	}
	int test_case = T;

	while (T-- > 0) {
		cin >> N;		
		cout << "#" << test_case - T << " " << (long long)cache[N] << endl;
	}


}