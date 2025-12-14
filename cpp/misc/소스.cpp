#include<iostream>
#include<string.h>
#include<algorithm>

using namespace std;

int cache[3][10000];
int n[10000];
int N;

int dp(int idx, int stack) {

	if (idx == N) return 0;

	int& ret = cache[stack][idx];
	if (ret != -1) return ret;
	
	return ret = stack == 2 ? 
		dp(idx + 1, 0) : max(dp(idx + 1, 0), n[idx] + dp(idx + 1, stack + 1));

}

int main() {

	cin >> N;
	for(int i =0; i < 3; i++)
		memset(cache[i], -1, sizeof(cache[i]));
	for (int i = 0; i < N; i++)
		cin >> n[i];
	cout << dp(0, 0) << endl;


}