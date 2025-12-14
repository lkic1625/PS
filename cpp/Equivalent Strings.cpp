#include<iostream>
#include<string>

using namespace std;

string a, b;

string strSort(string a) {
	if (a.size()% 2) return a;
	string left = strSort(a.substr(0, a.size() / 2));
	string right = strSort(a.substr(a.size() / 2, a.size() / 2));
	return left > right ? left + right : right + left;

}

int main() {
	cin >> a >> b;
	cout << (strSort(a) == strSort(b) ? "YES\n" : "NO\n");
}