#include<iostream>
#include<algorithm>
#include<string.h>
using namespace std;

int N, L, C;
double w[1001], psum[1001];

int main() {

	cin >> C;
	while (C-- > 0) {
		double ans = 100000;
		cin >> N >> L;
		for (int i = 1; i <= N; i++) {
			cin >> w[i];
			psum[i] = w[i] + psum[i - 1];
		}
		for (int i = 0; i <= N; i++) {
			for (int j = i + L; j <= N; j++) {
				ans = min(ans, (psum[j] - psum[i]) / (j - i));
			}
		}
		printf("%.8f\n", ans);

	}

}