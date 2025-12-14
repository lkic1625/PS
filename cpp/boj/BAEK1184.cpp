#include<iostream>

using namespace std;

const int MAX_N = 50 + 3;

int N;
int A[MAX_N][MAX_N], B[MAX_N][MAX_N];
int sum_of_A[MAX_N][MAX_N], sum_of_B[MAX_N][MAX_N];

inline int calc_sum(int start_x, int start_y, int end_x, int end_y, int sum[MAX_N][MAX_N]) {
	return (sum[end_y][end_x] - sum[end_y][start_x]) - (sum[start_y][end_x] - sum[start_y][start_x]);
}


int brute_force() {
	int ret = 0;

	for (int i = 1; i < N; i++) {
		for (int j = 1; j < N; j++) {
			int sum_A = sum_of_A[i][j];
			int sum_B = sum_of_B[i][j];
			for (int k = i + 1; k <= N; k++) {
				for (int l = j + 1; l <= N; l++) {
					int counter_sum_A = calc_sum(j + 1, i + 1, l, k, sum_of_A);
					int counter_sum_B = calc_sum(j + 1, i + 1, l, k, sum_of_B);
					if (counter_sum_A == sum_A) ret += 1;
					if (counter_sum_B == sum_B) ret += 1;
				}
			}

		}
	}

	return ret;
}


int main() {
	cin >> N;
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++) {
			cin >> A[i][j];
			B[i][N - j + 1] = A[i][j];
		}
	}

	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++) {
			A[j][i] = A[j - 1][i] + A[j][i];
			B[j][i] = B[j - 1][i] + B[j][i];
		}
	}

	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++) {
			sum_of_A[i][j] = sum_of_A[i][j - 1] + A[i][j];
			sum_of_B[i][j] = sum_of_B[i][j - 1] + B[i][j];
		}
	}

	int ans = brute_force();
	cout << ans;
}