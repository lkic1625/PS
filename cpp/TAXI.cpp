#include<iostream>
#include<algorithm>
using namespace std;

int N, ans = 0;
int n[5];

int main() {

	cin >> N;
	for (int i = 0; i < N; i++) {
		cin >> n[0];
		n[n[0]]++;
	}
	n[1] -= n[3] + 2 * (n[2] % 2);
	cout << n[4] + n[3] + (n[2] + 1) / 2 + (n[1] > 0 ? (n[1] + 3) / 4 : 0);

}