#include<iostream>
#include<string>

using namespace std;

const string EMPTY_STRING = "";
const int MAX = 3; //length(['A', 'B', 'C'])

struct Counter {
	int A, B, C;
	int to_index() {
		return A * 2500 + B * 50 + C;
	}

	Counter minus_A() {
		return { A - 1, B, C };
	}
	Counter minus_B() {
		return { A, B - 1, C };
	}
	Counter minus_C() {
		return { A, B, C - 1 };
	}
	bool is_empty() {
		return A == 0 && B == 0 && C == 0;
	}
};

int alphabet_to_index(char alp) {
	if (alp < 'A') { 
		throw "illeagal argument exception"; 
	}
	return alp - 'A';
}

Counter counter;
string S;
string cache[3 + 1][3 + 1][50 * 50 * 50 + 50 * 50 + 50 + 1];

string dp(int u, int v, Counter counter) {
	if (counter.is_empty()) { //counter == { 0, 0, 0 }
		return EMPTY_STRING;
	}
	
	string& ret = cache[u][v][counter.to_index()];
	if (ret.length() != 0) {
		return ret;
	}
	
	ret = S + S;

	if (counter.A > 0) {
		string branch = 'A' + dp(v, alphabet_to_index('A'), counter.minus_A());
		ret = branch.size() >= S.size() * 2 ? ret : branch;
	}
	if(counter.B > 0 && v != alphabet_to_index('B')){
		string branch = 'B' + dp(v, alphabet_to_index('B'), counter.minus_B());
		ret = branch.size() >= S.size() * 2 ? ret : branch;
	} 
	if (counter.C > 0 && u != alphabet_to_index('C') && v != alphabet_to_index('C')) {
		string branch = 'C' + dp(v, alphabet_to_index('C'), counter.minus_C());
		ret = branch.size() >= S.size() * 2 ? ret : branch;
	}
	
	return ret;

}

int main() {
	cin >> S;
	int a = 0, b = 0, c = 0;
	for(char employee : S) {
		switch (employee)
		{
		case 'A':
			a += 1;
			break;
		case 'B' :
			b += 1;
			break;
		case 'C':
			c += 1; 
			break;
		default:
			throw "Unprocessable arg exception";
		}
		
	}
	counter = { a, b, c };
	string ans = dp(MAX, MAX, counter);
	if (ans.length() == S.length()) {
		cout << ans;
	}
	else {
		cout << -1;
	}
}