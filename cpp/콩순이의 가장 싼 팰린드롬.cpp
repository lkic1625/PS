#include<string>
#include<vector>
#include<algorithm>
#include<iostream>

using namespace std;

int K, L;
int cache[2000][2000];
int alp[26];
string str;

int dp(int start, int end) {

	if (start >= end) return 0;
	int& ret = cache[start][end];
	if (ret != -1) return ret;

	ret = 100000000;
	if (str[start] == str[end]) return ret = min(ret, dp(start + 1, end - 1));
	ret = min(ret, alp[str[start] - 'a'] + dp(start + 1, end));
	ret = min(ret, alp[str[end] - 'a'] + dp(start, end - 1));

	return ret;
}

int main(int argc, char** argv)
{
	int test_case;
	int T;
	int temp1, temp2;
	cin >> T;
	/*
	   여러 개의 테스트 케이스가 주어지므로, 각각을 처리합니다.
	*/
	for (test_case = 1; test_case <= T; ++test_case)
	{
		for (int i = 0; i < 2000; i++)
			for (int j = 0; j < 2000; j++)
				cache[i][j] = -1;

		cin >> L >> K;
		cin >> str;
		for (int i = 0; i < K; i++) {
			cin >> temp1 >> temp2;
			alp[i] = min(temp1, temp2);
		}
		cout << "#" << test_case << " " << dp(0, L - 1) << endl;

	}
	return 0;//정상종료시 반드시 0을 리턴해야합니다.
}