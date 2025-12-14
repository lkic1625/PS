#include<iostream>

using namespace std;

bool cache[10000000];
int arr[11];
int n, k;

int travel(int depth, int num, int use) {
	if (depth > k) {
		return false;
	}
	int ret = cache[num] == false;
	cache[num] = true;
	for (int i = 0; i < n; i++) {
		if (!(use ^ (1 << i))) continue;
		if (arr[i] >= 10) ret += travel(depth + 1, num * 100 + arr[i], use | (1 << i));
		else ret += travel(depth + 1, num * 10 + arr[i], use | (1 << i));
	}
	return ret;
}

int main() {
	cin >> n >> k;
	for (int i = 0; i < n; i++) {
		cin >> arr[i];
	}
	cout << travel(0, 0, 0) << endl;
	/*for (int i = 0; i < 100000000; i++) {
		if (cache[i] == true) cout << i << endl;
	}*/
}