/*
Dynamic Programming
C. Hard problem
https://codeforces.com/problemset/problem/706/C

Input
The first line of the input contains a single integer n (2 ≤ n ≤ 100,000) — the number of strings.

The second line contains n integers c i (0 ≤ c i ≤ 10^9), the i-th of them is equal to the amount of energy Vasiliy has to spent in order to reverse the i-th string.

Then follow n lines, each containing a string consisting of lowercase English letters. 
The total length of these strings doesn't exceed 100,000.

Output
If it is impossible to reverse some of the strings such that they will be located in lexicographical order, print  - 1. 
Otherwise, print the minimum total amount of energy Vasiliy has to spent.

*/

#include<iostream>
#include<string>
#include<algorithm>

typedef long long ll;
using namespace std;

enum CASE {
	NN, //none < none
	NR, //none < reverse
	RN, //reverse < none
	RR  // reverse < reverse
};

//values
const ll ENERGY_MAXIMUM = 1.0e9;
const int NUMBER_OF_CASES = 4;
const ll ELEMENT_MAXIMUM = 1.0e5;
const ll ANSWER_MAXIMUM = ELEMENT_MAXIMUM * ENERGY_MAXIMUM + 1;

//variables
string letters[ELEMENT_MAXIMUM + 1];
ll c[ELEMENT_MAXIMUM + 1], n;
ll cache[ELEMENT_MAXIMUM + 1][NUMBER_OF_CASES];

int main() {

	//fast I/O
	ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
	
	//input
	cin >> n;
	for (int i = 0; i < n; i++) {
		cin >> c[i];
	}
	for (int i = 0; i < n; i++) {
		cin >> letters[i];
	}

	//initializing
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < NUMBER_OF_CASES; j++) {
			cache[i][j] = ANSWER_MAXIMUM;
		}
	}
	letters[n] = "zz" + letters[n - 1] + "zz";
	//above 

	//dp
	string prefixReverse, suffixReverse;
	for (int i = n - 1; i >= 0; i--) {

		prefixReverse.resize(letters[i].size());
		suffixReverse.resize(letters[i + 1].size());
		reverse_copy(letters[i].begin(), letters[i].end(), prefixReverse.begin());
		reverse_copy(letters[i + 1].begin(), letters[i + 1].end(), suffixReverse.begin());
		//the above function can be used, including algorithm header file.

		bool flag =
			letters[i] <= letters[i + 1] ||
			letters[i] <= suffixReverse ||
			prefixReverse <= letters[i + 1] ||
			prefixReverse <= suffixReverse;
		//if 4 cases are false, flag is false.
		//this means strings can't be sorted in lexicographically ordered.

		if (letters[i] <= letters[i + 1]) {//NN 
			cache[i][NN] = min(cache[i + 1][NN], cache[i + 1][NR]);
		} 
		if (letters[i] <= suffixReverse) {//NR
			cache[i][NR] = min(cache[i + 1][RN], cache[i + 1][RR]);
		} 
		if (prefixReverse <= letters[i + 1]) {//RN
			cache[i][RN] = min(cache[i + 1][NN], cache[i + 1][NR]) + c[i];
		} 
		if (prefixReverse <= suffixReverse) {//RR
			cache[i][RR] = min(cache[i + 1][RN], cache[i + 1][RR]) + c[i];
		} 
		if(!flag) {
			for (int j = 0; j < NUMBER_OF_CASES; j++) {
				cache[i][j] = -1;
			}
		}
	}

	//find minimum total amount of energy Vasiliy has to spent.
	ll ans = ANSWER_MAXIMUM;
	for (int i = 0; i < NUMBER_OF_CASES; i++) {
		ans = min(ans, cache[0][i]);
	}

	//output
	cout << (ans == ANSWER_MAXIMUM ? -1 : ans);
	//the key approach in this problem
	//in case the impossible number, ANSWER_MAX, is continuously transmitted and output.
	//-1 should be printed instead of ANSWER_MAX.
}