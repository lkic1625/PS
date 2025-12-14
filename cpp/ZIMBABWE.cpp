#include<iostream>
#define MOD %
using namespace std;

const int PRIME = 1'000'000'007;

/*
INPUT
4
321 3
123 3
422 2
12738173912 7

OUTPUT
5
0
2
11033
*/

int e, m, c;
int multiples[10];
int counter[10];
int digits[15];

// state is bit for counting numbers.
int dp(int bef, int cur, int state) {
	

}

int main() {
	cin >> c;
	while (c-- > 0) {
		cin >> e >> m;
		for (int i = 1; i < 10; i++) {
			multiples[i] = multiples[i - 1] * m;
		}
		int i = 0;
		for (i; e != 0; i++, e /= 10) {
			digits[i] = e % 10;
			counter[e % 10] += 1;
		}

	}
}
