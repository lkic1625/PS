//사전 순 괄호 문자열
//catalan number
//https://swexpertacademy.com/main/code/problem/problemDetail.do?contestProbId=AWcPjE1qAFkDFAU4&categoryId=AWcPjE1qAFkDFAU4&categoryType=CODE
#include<iostream>
#include<string>
#include<algorithm>
#include<string.h>
const long long INF = 1e18 + 1;
using namespace std;

int T, N;
long long K, cache[101][101];

void generate(int n, int m, string str) {
	if (n == N && m == N) {
		cout << str << endl;
		return;
	}
	if (n < N) generate(n + 1, m, str + "(");
	if (n > m) generate(n, m + 1, str + ")");

}

long long dp(int n, int m)
{
	if (n == 0 && m == 0) return 1;
	if (n < 0 || m < 0 || n > m) return 0;

	long long &ret = cache[n][m];
	if (ret != -1) return ret;

	return ret = min(dp(n - 1, m) + dp(n, m - 1), INF);
}

void nth(int n, int m, long long k) {

	if (n == 0 && m == 0) {
		cout << endl;
		return;
	}

	long long q = dp(n - 1, m);
	if (k < q) {
		printf("(");
		nth(n - 1, m, k);
	}
	else {
		printf(")");
		nth(n, m - 1, k - q);
	}
}

int main() {

	memset(cache, -1, sizeof(cache));

	cin >> T;
	int test_case = T;
	
	
	while (T-- > 0) {
		scanf("%d %lld", &N, &K);
		if (dp(N, N) < K) {
			cout << "#" << test_case - T << " ";
			cout << ")(" << endl;
		}
		else {
			cout << "#" << test_case - T << " ";
			nth(N, N, K - 1);
		}
	}

}