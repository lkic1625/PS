#include<iostream>

using namespace std;

using ull = unsigned long long;
int N;

ull add_with_mod(ull a, ull b, ull mod) {
	a = a % mod;
	b = b % mod;
	return (a + b) % mod;
}

ull mul_with_mod(ull a, ull b, ull mod) {
	a = a % mod;
	b = b % mod;
	ull ret = 0;
	while (b > 0) {
		if (b % 2 == 1) {
			ret = add_with_mod(ret, a, mod);
		}
		a = add_with_mod(a, a, mod);
		b = b / 2;
	}

	return ret;
}

//return a^b % mod
ull pow_with_mod(ull a, ull b, ull mod) {
	a = a % mod;
	ull ret = 1ULL;
	while (b > 0) {
		if (b % 2 == 1) {
			ret = (ret * a) % mod;
		}
		a = (a * a) % mod;
		b = b / 2;
	}

	return ret;
}


bool miller_rabin_primality_test(ull n, ull a) {

	ull d = n - 1;
	while (d % 2 == 0) {
		if (pow_with_mod(a, d, n) == n - 1) {
			return true;
		}
		d = d / 2;
	}

	ull pow_of_a_d = pow_with_mod(a, d, n);
	return pow_of_a_d == n - 1 || pow_of_a_d == 1;

}

bool is_prime(ull n) {
	if (n <= 1) return false;
	if (n <= 10000ULL) {
		for (ull i = 2; i * i <= n; i++) {
			if (n % i == 0) {
				return false;
			}
		}
		return true;
	}
	for (ull a : {2, 3, 5, 7, 11}) {
		if (!miller_rabin_primality_test(n, a)) {
			return false;
		}
	}
	return true;
}


int main() {
	ull measure;
	int ans = 0;
	cin >> N;
	for (int i = 0; i < N; i++) {
		cin >> measure;
		if (is_prime(2 * measure + 1)) {
			ans++;
		}
	}

	cout << ans << '\n';
}