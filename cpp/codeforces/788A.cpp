#include<iostream>
#include<algorithm>
using namespace std;

int n, i;
long long a[100001];
long long s[100001];//|a[i] - a[i + 1]|을 저장한 배열.

//kadane algorithm
long long dp(int l) {
	long long ret = 0, temp = 0;
	for (i = 0; i < n - 1; i++) {
		temp += s[i] * (i % 2 ? l : -l);
		ret = max(ret, temp);
		if (temp < 0) temp = 0;
	}
	return ret;
}


int main() {
	//input
	cin >> n;
	for (i = 0; i < n; i++)
		cin >> a[i];
	for (i = 0; i < n - 1; i++) 
		s[i] = abs(a[i] - a[i + 1]);
	//output
	cout << max(dp(1), dp(-1)) << endl;

}