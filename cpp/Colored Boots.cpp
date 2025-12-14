//https://codeforces.com/contest/1141/problem/D
#include<queue>
#include<algorithm>
#include<iostream>
#include<string>

using namespace std;
vector<pair<int, int>> ans;
queue<int> r[27], l[27];
int n;
string lstr, rstr;

int main() {
	cin >> n >> lstr >> rstr;
	
	for (int i = 0; i < n; i++) {
		
		if (lstr[i] == '?') l[26].push(i);
		else l[lstr[i] - 'a'].push(i);
		if (rstr[i] == '?') r[26].push(i);
		else r[rstr[i] - 'a'].push(i);
	}
	for (int i = 0; i < 26; i++) {
		int len = min(l[i].size(), r[i].size());
		for(int j = 0; j < len; j++){
			ans.push_back(make_pair(l[i].front(), r[i].front()));
		//	printf("%d %d\n", l[i].front(), r[i].front());
			l[i].pop(); r[i].pop();
		}
	}
	for (int i = 0; i < 27; i++) {
		while (l[i].size() != 0 && r[26].size()) {
			ans.push_back(make_pair(l[i].front(), r[26].front()));
		//	printf("%d %d\n", l[i].front(), r[26].front());
			l[i].pop(); r[26].pop();
		}
		while (r[i].size() != 0 && l[26].size() != 0) {
			ans.push_back(make_pair(l[26].front(), r[i].front()));
		//	printf("%d %d\n", l[26].front(), r[i].front());
			l[26].pop(); r[i].pop();
		}
	}
	printf("%d\n", ans.size());
	for (auto iter = ans.begin(); iter != ans.end(); iter++) {
		printf("%d %d\n", (*iter).first + 1, (*iter).second + 1);
	}
}