#include<iostream>

using namespace std;

int main() {
	int n, m;
	cin >> n >> m;
	long long ans = 0;
	int temp = 1;
	int task;
	for (int i = 0; i < m; i++) {
		scanf_s("%d", &task);
		if (task >= temp) {
			ans += task - temp;
		}
		else {
			ans += task + n - temp;
		}
		temp = task;
	}
	cout << ans;
}