#include<iostream>
#define MOD  1000000007

int T, N, n;
long long cache[1000002];

long long mul(long long x, long long y) {
	long long ans = 1;
	while (y > 0) {
		if (y % 2 != 0) {
			ans *= x;
			ans %= MOD;
		}
		x *= x;
		x %= MOD;
		y /= 2;
	}
	return ans;
}

int main() {

	for (int i = 0; i < n; i++) {


	}

	scanf_s("%d", &T); //9999�� �´� ����?.
	int test_case = T;
	cache[1] = 3;
	for (int idx = 2; idx <= 1000000; idx++) {
		n++;
		long long& ret = cache[idx];
		ret = cache[n] * 3 * (4 * n + 2);
		ret %= MOD;
		//���� ������ �������� ��?
		ret *= mul(n + 2, MOD - 2);
		ret %= MOD;
		if (ret <= 0) printf("%lld", ret);
	}
	while (T-- > 0) {
		
		scanf_s("%d", &N);
		printf("#%d %lld\n", test_case - T, cache[N]);
	}
	return 0;
}