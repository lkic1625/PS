//https://www.acmicpc.net/problem/1671
//상어의 저녁식사
#include<iostream>
#include<vector>
#include<set>
#include<queue>
using namespace std;

struct shark {
	int a, b, c, iv;
	shark(int a, int b, int c, bool iv = true) :a(a), b(b), c(c), iv(iv){}
	inline bool operator<(const shark &rv) {
		return this->a < rv.a && this->b < rv.b && this->c < rv.c;
	}
};

set<pair<int, int>> l;
int matrix[50][50];
shark s[51];
int n;

int bfs() {

}

int main() {
	cin >> n;
	int a, b, c;
	for (int i = 0; i < n; i++) {
		cin >> a >> b >> c;
		s[i] = shark(a, b, c);
	}
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			if (s[i] < s[j])
				matrix[j][i] = 1;
		}
	}
}