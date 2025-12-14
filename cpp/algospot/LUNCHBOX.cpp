#include<iostream>
#include<vector>
#include<algorithm>

using namespace std;

int C, n;
int m[10000], e[10000];
vector<pair<int, int> > v;

int main() {
	cin >> C;
	while (C-- > 0) {
		int ans = 0,temp = 0;
		cin >> n;
		for (int i = 0; i < n; i++)
			cin >> m[i];
		for (int i = 0; i < n; i++)
			cin >> e[i];
		for (int i = 0; i < n; i++)
			v.push_back(make_pair(e[i], m[i]));
		sort(v.begin(), v.end());
		for (auto i = v.rbegin(); i != v.rend(); i++) {
			
			if (temp >= i->first + i->second)
				temp -= i->second;
			else {
				ans += i->first + i->second - temp;
				temp = i->first;
			}
		}
		v.clear();
		cout << ans << endl;

		

	}
}