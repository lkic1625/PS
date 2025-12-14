#include<iostream>
#include<set>
#include<queue>
using namespace std;

int C, n, temp, ans;
priority_queue<int, vector<int>, greater<int>> s;
multiset<int> str;
int main() {
	cin >> C;
	while (C-- > 0)
	{
		ans = 0; temp = 0;
		cin >> n;
		for (int i = 0; i < n; i++) {
			cin >> temp;
			s.push(temp);
			str.insert(temp);
		}	
		int tmp = 0;
		//priorty queue로도 해보자
		while (str.size() != 1) {
			auto iter1 = str.begin(); auto iter2 = iter1++;
			tmp += s.top(); s.pop();
			tmp += s.top(); s.pop();
			s.push(tmp);
			temp = *iter1 + *iter2;
			str.erase(iter1); str.erase(iter2);
			str.insert(temp);
			ans += temp;
		}
		cout << ans << endl;
		str.clear();		
	}
}