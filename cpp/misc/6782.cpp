#include<iostream>
#include<algorithm>
#include<math.h>
using namespace std;

long long cache[1000002];
long long T, N;

long long solve(long long n) {
	if (n == 2) return 0;

	long long bs = cache[(lower_bound(cache, cache + 1000001, n) - cache)];
	if (bs == n) return solve(sqrt(n)) + 1;
	else return bs - n + solve(bs);
}

int main() {
	cin >> T;
	int test_case = T;
	for (long long i = 1; i < 1000001; i++) {
		cache[i] = i * i;
	}

	while (T-- > 0) {
		scanf("%lld", &N);
		printf("#%d %lld\n", test_case - T, solve(N));
	}
}