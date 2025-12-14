#include <iostream>
#include<algorithm>
#define MAX 1000000

using namespace std;
long long cache[MAX + 1];
int cache2[10001][100];
int cache3[MAX + 1];
int Answer;
int x, y;

int dp(int num) {

	if (num <= 1 && num >= 0) return num;

	int n = lower_bound(cache, cache + MAX + 1, num) - cache;
	int n2 = lower_bound(cache, cache + MAX + 1, num / 2) - cache;
	if (num < cache[n]) n--;
	if (num / 2 < cache[n2]) n2--;
	return min(n2 + dp(num - cache[n2]), n + dp(num - cache[n]));
}

int dp2(int num, int stack) {
	if (num == 0) return 0;
	if (num < 0) return 1000000;
	int& ret = cache2[num][stack];
	if (ret != 0) return ret;
	return ret = min(1 + dp2(num - 1, 2), 1 + dp2(num - stack, stack + 1));
}

int main(int argc, char** argv)
{
	int T, test_case;
	for (int i = 1; i < MAX + 1; i++) {
		cache[i] = cache[i - 1] + i;
	}
	

	cin >> T;
	for (test_case = 0; test_case < T; test_case++)
	{
		cin >> x >> y;
		Answer = 0;
		for (int i = x; i <= y; i++) {
			cout << i << "  " << dp(i) <<  endl;
		
			Answer = max(Answer, dp(i));
		}
		
		cout << "Case #" << test_case + 1 << endl;
		cout << Answer << endl;
	}

	return 0;//Your program should return 0 on normal termination.
}