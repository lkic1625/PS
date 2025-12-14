#include<iostream>

using namespace std;

int T, N, M, C;
int honey[101];
bool arr[5];
int max, i, j, sum, sqr_sum;

void isMax(const int& posit1, const int& posit2);

int main() {
	bool jump_flag;
	int limit, check, startJ;

	cin >> T;
	while (T-- > 0)
	{

		max = 0;

		cin >> N >> M >> C;

		for (i = 1; i <= N * N; i++) {
			cin >> honey[i];
		}

		jump_flag = M * 2 > N;
		limit = N * N - M + 1;
		check = N - M + 1;
		startJ = jump_flag ? N + 1 : 1 + M;

		for (int i = 1; i <= limit; i++) {

			if (i % N + M > check) startJ = (i / N + 1) * N + 1;
			else startJ = i + M;

			for (int j = startJ; j <= limit; j++) {
				isMax(i, j);
				if (j % N == check) j += M - 1;
			}

			if (i % N == check)  i += M - 1;

		}
		cout << max << endl;

	}



	return 0;
}

int load_max(const int& pos, const int& stack) {

	for (int i = 0; i < M - stack; i++) {
		arr[i] = true;
	}

}

void isMax(const int & posit1, const int & posit2)
{
	sqr_sum = 0;

}
