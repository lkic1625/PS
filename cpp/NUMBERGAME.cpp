#include<iostream>
#include<vector>
#include<algorithm>

using namespace std;

int C, n;
int cache[50][50], arr[50];

int dp(int start, int end, bool check) {
	
	if (start == end) return arr[start];
	
	int& ret = cache[start][end];
	if (ret != -50001) return ret;

	ret = max(ret, arr[start] - dp(start + 1, end, !check));
	ret = max(ret, arr[end] - dp(start, end - 1, !check));
	if (end - start >= 2) {
		ret = max(ret, -dp(start + 2, end, !check));
		ret = max(ret, -dp(start, end - 2, !check));
	}

	return ret;
}



int main() {
	cin >> C;
	while (C-- > 0)
	{
		cin >> n;
		for (int i = 0; i < 50; i++)
			for (int j = 0; j < 50; j++)
				cache[i][j] = -50001;
		
		for (int i = 0; i < n; i++)
			cin >> arr[i];
		
		cout << dp(0, n - 1, false) << endl;
		
	}
	
	
}