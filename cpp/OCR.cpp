#include<vector>
#include<string>
#include<iostream>
#include<algorithm>
#include<string.h>


using namespace std;

int m, q, n;
vector<string> arr, ans;
vector<int> cr;

int i, j;
double T[500][500], M[501][500];
double cache[501][101];
//double cache[500];
int choice[501][101];


void reconstructor(int prv, int idx) {
	if (choice[prv + 1][idx] != -1) {
		ans.push_back(arr[choice[prv + 1][idx]]);
		reconstructor(choice[prv + 1][idx], idx + 1);
	}
}

double dp(int prv, int idx) {

	if (idx == n) return 0;

	double& ret = cache[prv + 1][idx];
	if (ret != 1.0) return ret;

	int bestNext = -1;
	
	ret = -1e299;
	for (int i = 0; i < m; i++) {
		double cand = M[i][cr[idx]] + T[prv + 1][i] + dp(i, idx + 1);
		if (ret < cand) {
			ret = cand;
			bestNext = i;
		}
	}

	choice[prv + 1][idx] = bestNext;

	return ret;

}


int main() {

	cin >> m >> q;
	arr.resize(m);
	for (i = 0; i < m; i++)
		cin >> arr[i];

	double temp1;
	for (i = 0; i <= m; i++)
		for (j = 0; j < m; j++) {
			cin >> temp1;
			T[i][j] = log10(temp1);
		}
	for (i = 0; i < m; i++)
		for (j = 0; j < m; j++) {
			cin >> temp1;
			M[i][j] = log10(temp1);
		}
			

	string temp;
	for (i = 0; i < q; i++) {
		cin >> n;
		cr.clear();
		ans.clear();
		for (j = 0; j < 501; j++) {
			for (int k = 0; k < 101; k++) {
				cache[j][k] = 1.0;
				choice[j][k] = -1;
			}
			
		}
		for (j = 0; j < n; j++) {
			cin >> temp;
			for (auto iter = arr.begin(); iter != arr.end(); iter++) {
				if (*iter == temp) {
					cr.push_back(iter - arr.begin());
					break;
				}
			}
		}
		dp(-1, 0);
		reconstructor(-1, 0);
		for (auto iter = ans.begin(); iter != ans.end(); iter++) {
			cout << *iter << " ";
		}
		cout << endl;

	}

}