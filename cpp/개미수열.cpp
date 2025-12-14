#include<iostream>
#include <string>
using namespace std;

int n;
const int MAX = 40 + 1;
string cache[MAX];

void countAndSay(int n) {
	//if (n == 1) return "1";
	string& ret = cache[n];
	string p = cache[n - 1];

	char bef = p[0];
	int count = 1;
	for (int i = 1; i < p.size(); i++) {
		
		if (bef == p[i]) count++;
		else {
			ret += (bef + to_string(count));
			bef = p[i];
			count = 1;
		}
	}
	
	ret = ret + "$";

	//return ret;
}

string solution(int n)
{
	//basis case
	cache[1] = "1$"; cache[2] = "11$";
	for (int i = 3; i <= n; i++) {
		countAndSay(i);
	}
	
	string answer = cache[n];
	
	return answer.substr(0, answer.size() - 1);
}

int main() {
	cin >> n;
	cout << solution(n);
}