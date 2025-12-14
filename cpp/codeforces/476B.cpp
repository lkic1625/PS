#include<iostream>
#include<string>
using namespace std;

string send, reci;
int cnt[3];

int getComb(int a, int b) {
	int ret = 1;
	for (int i = b + 1; i <= a; i++) {
		ret *= i;
	}
	for (int j = a - b; j > 0; j--) {
		ret /= j;
	}
	return ret;
}

int main() {
	cin >> send >> reci;
	for (auto iter = send.begin(); iter != send.end(); iter++) {
		if (*iter == '+')
			cnt[0]++;
		else if (*iter == '-')
			cnt[0]--;
	}
	for (auto iter = reci.begin(); iter != reci.end(); iter++) {
		if (*iter == '+')
			cnt[1]++;
		else if (*iter == '-')
			cnt[1]--;
		else
			cnt[2]++;
	}
	int sum = abs(cnt[1] - cnt[0]);
	if (cnt[2] - sum < 0 || (cnt[2] - sum) % 2) {
		printf("%.12f", 0.0);
	}
	else {
		printf("%.12f", getComb(cnt[2], sum + (cnt[2] - sum) / 2) * pow(0.5, cnt[2]));
	}
}