#include<iostream>
#include<string>
#include<algorithm>
using namespace std;

int N, K;
unsigned int bit[100];
const string alp = "bdefghjklmopqrsuvwxyz";

int main() {
	cin >> N >> K;
	string input;
	for (int i = 0; i < N; i++) {
		cin >> input;
		for(auto iter : input){
			auto pos = alp.find(iter);
			if(pos < alp.size())
				bit[i] |= 1 << (int)(pos);
		}
	}
	int ans = 0;
	for (int subset = 0; subset < (1 << alp.size()); subset++) {
		int cnt = __builtin_popcount(subset); //only using in g++
		if (cnt != K - 5) continue;
		int temp = 0;
		for (int i = 0; i < N; i++) {
			if ((bit[i] & (subset)) == bit[i]) temp++;
		}
		ans = max(ans, temp);
	}
	cout << ans;
}