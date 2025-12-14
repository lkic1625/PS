#include<iostream>
#include<string>

using namespace std;

const int MAX = 26;

int N;
string words[MAX];
int word_to_bits[MAX];
long combination;

int traversal(int i, int bit) {

}

int main() {
	cin >> N;
	for (int i = 0; i < N; i++) {
		for (char alphabet : words[i]) {
			word_to_bits[i] |= 1 << (alphabet - 'A');
		}
	}
	combination = (1 << (N + 1)) - 1;
	for (int subset = combination; subset; (subset - 1) & combination) {
		//2^26 TLE
	}
	int a = 0;
	//or == || and == &&
	if (a < 0 or a > 10 and a == 10 xor a == 10) {

	}

}