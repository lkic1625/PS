#include<iostream>
#include<algorithm>
#include<queue>

using namespace std;

const int MAX = 100'000;

struct CommutingDistance {
	int h, o;
};

int n, t, h, o;
CommutingDistance commutingDistances[MAX + 1];

int main() {
	cin >> n;
	for (int i = 0; i < n; i++) {
		cin >> h >> o;
		commutingDistances[i] = { h, o };
	}

	sort(commutingDistances, commutingDistances + n, [](CommutingDistance lv, CommutingDistance rv) {
		return lv.h < rv.h;
	});

	for (int l = 0, r = 0; l <= r && r < n; r++) {
		if (commutingDistances[l].h - commutingDistances[r].h > d) {

		}
	}
	
}