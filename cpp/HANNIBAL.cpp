#include<iostream>
#include<string.h>
using namespace std;

int c, n, d, p, t, q;
int i, j, k;
bool isConnect[50][50];
int ways[50];
double cache[50][50][100];

double solve(int p, int q, int d) {

	
	if (d == 1)
		return isConnect[p][q] ? (1.0 / ways[p]) : 0;

	double& ret = cache[p][q][d];
	if (ret != -1)
		return ret;

	ret = 0;
	
	for (int i = 0; i < n; i++)
		if (isConnect[p][i])
			ret += (1.0 / ways[p]) * solve(i, q, d - 1);

	return ret;
			
}

int main() {

	cin >> c;
	
	cout << fixed;
	cout.precision(8);

	while (c-- > 0)
	{
		
		memset(ways, 0, sizeof(ways));
		for (i = 0; i < 50; i++)
			for (j = 0; j < 50; j++)
				for (k = 0; k < 100; k++)
					cache[i][j][k] = -1;


		cin >> n >> d >> p;
		for (i = 0; i < n; i++) {
			for (j = 0; j < n; j++) {
				cin >> isConnect[i][j];
				if (isConnect[i][j])
					ways[i]++;
			}
		}
		cin >> t;
		for (i = 0; i < t; i++){
			cin >> q;
			cout << solve(p, q, d) << " ";
		}
		cout << endl;
		
	}
}