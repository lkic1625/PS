//https://codeforces.com/contest/1141/problem/C
#include<iostream>
#include<algorithm>
#define BUFF 200000

using namespace std;

int n, q[BUFF + 1], m[2 * BUFF + 1];
bool isPermut(int idx) {
	for (int i = 0; i < n; i++) {
		if (m[idx + i] != 1) return false;
	}
	return true;
}

int main() {
	int crtIdx = BUFF, minIdx = BUFF;
	scanf_s("%d", &n);
	for (int i = 1; i < n; i++)
		scanf_s("%d", &q[i]);
	for (int i = 0; i < n; i++) {
		crtIdx += q[i];
		if (crtIdx > BUFF * 2 || crtIdx < 0) break;
		m[crtIdx] = 1;
		minIdx = min(minIdx, crtIdx);
	}
	if (isPermut(minIdx)) {
		int element = BUFF - minIdx + 1;
		for (int i = 0; i < n; i++) {
			element += q[i];
			printf("%d ", element);
		}
	}
	else cout << -1;
	


}