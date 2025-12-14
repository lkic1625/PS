#include<iostream>

using namespace std;

int gcd(int i, int k) {
	
	if (i % k == 0) return k;
	else return gcd(k, i % k);
}


int fac(int i) {
	if (i == 0) return 1;
	return i * fac(i - 1);
}

int T, N, K;

int gcd2(int n, int k) {
	if(n == 0) return 1;
	if (k <= N) return k;
	if (k % n == 0) return n * gcd2(n - 1, k / n);
	else return gcd2(n - 1, k);
}

int main() {
	cin >> T;
	int test_case = T;
	while (T-- > 0)
	{
		cin >> N >> K;
		
		cout << "#" << test_case - T << " " << gcd2(N,K) << endl;
	}

}