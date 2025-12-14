#include <iostream>

using namespace std;

int cache[1000001];
int cache2[1000001];
int Answer;

int main(int argc, char** argv)
{
	int T, test_case;

	cin >> T;

	for (int i = 2; i < 1000001; i++) {
		if (i % 2) cache[i] = cache[(i + 1) / 2] + 2;
		else cache[i] = cache[i / 2] + 1;
		cache2[i] += cache2[i - 1] + cache[i];
	}
	int n1, n2;
	for (test_case = 0; test_case < T; test_case++)
	{
		cin >> n1 >> n2;
		Answer = cache2[n2] - cache2[n1] + cache[n1];
		
		printf("Case #%d\n", test_case + 1);
		printf("%d\n", Answer);
	}

	return 0;//Your program should return 0 on normal termination.
}