#include<iostream>
#include<string>
#include<set>
using namespace std;

int main() {
	string num;
	multiset<int> s;
	cin >> num;
	for (auto iter : num) {
		s.insert(iter - 48);
	}
	if (*s.begin() != 0) cout << -1;
	else {
		for (auto iter : s) {
			cout << iter;
		}
	}
}