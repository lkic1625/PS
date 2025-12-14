#include<iostream>
#include<algorithm>
#include<cmath>
constexpr auto INF = 10000000;
using namespace std;

int C, N, S;

int n[100];
int cache[11][100];

int dp(int start, int stack);

int main() {

	cin >> C;

	while (C-- > 0)
	{
		for (int i = 0; i < 11; i++) 
			for (int j = 0; j < 100; j++) 
				cache[i][j] = INF;

		cin >> N >> S;
		S = min(N, S);
		
		for (size_t i = 0; i < N; i++)
			cin >> n[i];
		
		

		sort(n, n + N);

		int result = INF;
		for (int i = 0; i < S; i++) {
			result = min(result, dp(i , 0));
		}

		cout << result << endl;
	}
}

int getSqureError(int start, int length, int sum) {

	double result = 0;
	int mean = (sum / (double)length) + 0.5;
	for (int i = 0; i < length; i++) 
		result += pow(n[start + i] - mean,2);
	return result;
}
int dp(int stack, int start)
{
	
	int& ret = cache[stack][start];
	if (ret != INF) return ret;

	int sum = 0;
	
	for (int i = start; i < N - stack; i++) {
		sum += n[i];
		ret = min(ret, dp(stack - 1, i + 1) + getSqureError(start, i - start + 1,sum));
	}

	if (stack == 0)
		return ret = getSqureError(start, N - start, sum);
	
	return ret;
}
