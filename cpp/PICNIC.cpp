#include<iostream>
#define FIRST 0
#define SECOND 1
using namespace std;


int C, n, m;

int p[2][45];
int cache[10][10];
bool check[10];
int solve(int head, int countingPair) {

	if (countingPair * 2 == n)
		return 1;

	int ret = 0;
	for (int i = head; i < m; i++) {
		if (!check[p[FIRST][i]] && !check[p[SECOND][i]]) {
			 check[p[FIRST][i]] =check[p[SECOND][i]] = true;
			ret += solve(i + 1, countingPair + 1);
			check[p[FIRST][i]] = check[p[SECOND][i]] = false;
		}
	}
	
	return ret;
	
}


int main()
{

	cin >> C;

	while (C-- > 0)
	{

		cin >> n >> m;

		for (int i = 0; i < m; i++) {
			cin >> p[FIRST][i];
			cin >> p[SECOND][i];
		}

		cout << solve(0,0) << endl;
	}
}
