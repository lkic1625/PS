//https://www.acmicpc.net/problem/13458
#include<iostream>
#include<string>
#include<algorithm>
#include<vector>
using namespace std;
int N, B, C;
int A[1000000];
int main() {
	cin >> N;
	for (int i = 0; i < N; i++) 
		cin >> A[i];
	
	cin >> B >> C;
	long long ans = N;
	for (int i = 0; i < N; i++)
		if (A[i] - B > 0)
			ans += (A[i] - B + C - 1) / C;

	cout << ans;


}