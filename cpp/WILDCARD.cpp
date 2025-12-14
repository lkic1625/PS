#include<iostream>
#include<string.h>
#include<string>
#include<set>

using namespace std;

int C, N;
int cache[101][101];
string wildcard, word;


bool dp(int n, int m) {

	//basis case
	if (n == wildcard.size())
		return m == word.size();
	if (m == word.size())
		return wildcard[n] == '*' && dp(n + 1, m);
		
	int& ret = cache[n][m];
	if (ret != -1) return ret;

	if (wildcard[n] == '?')
		return ret = dp(n + 1, m + 1);
	if (wildcard[n] == '*')
		return ret = dp(n, m + 1) || dp(n + 1, m);

	return ret = wildcard[n] == word[m] && dp(n + 1, m + 1);
}

int main() {

	cin >> C;
	while (C-- > 0) {
		set<string> dict;
		cin >> wildcard >> N;
		for (int i = 0; i < N; i++) {
			memset(cache, -1, sizeof(cache));
			cin >> word;
			if (dp(0, 0)) dict.insert(word);
		}
		for (auto iter = dict.begin(); iter != dict.end(); iter++) {
			cout << *iter << endl;
		}
	}
}