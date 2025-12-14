#include<iostream>

using namespace std;

long long memoization[1000000];



long long F(int n) {
	if (n < 3) return 1;
	if (memoization[n] != 0) return memoization[n];
	else return memoization[n] = F(n - 1) + F(n - 2);
}

int main() {
	for (int n = 50; n > 1; n--) {
		printf("%I64d\n", F(n));
	}
}