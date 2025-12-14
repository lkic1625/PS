#include<iostream>
#include<string>
#include<algorithm>
#include<vector>
using namespace std;

enum cons {
	VOLUME,
	DESPERATION
};
int C, N, W;
int cache[101][1000];
int pack[101][2], choice[101][1000];
vector<int> ans;
string name[101];

void getans(int pos, int w) {
	if (choice[pos + 1][w] != -1) {
		ans.push_back(choice[pos + 1][w]);
		getans(choice[pos + 1][w],w - pack[choice[pos + 1][w]][VOLUME]);
	}
}

int dp(int idx, int vol) {

	if (vol < 0) return -3000 - pack[idx][DESPERATION] ;
	
	int& ret = cache[idx + 1][vol];
	if (ret != -1) return ret;

	int bestNext = -1; 
	
	for (int i = idx + 1; i < N; i++) {
		int cand =  pack[i][DESPERATION] + dp(i, vol - pack[i][VOLUME]);
		if (ret < cand) {
			ret = cand;
			bestNext = i;
		}
	}

	choice[idx + 1][vol] = bestNext;
	
	return ret = ret == -1 ? 0 : ret;


}

int main() {
	cin >> C;
	pack[0][DESPERATION] = 0;
	pack[0][VOLUME] = 0;
	while (C-- > 0)
	{
		
		for (int i = 0; i < 101; i++) {
			memset(cache[i], -1, sizeof(cache[i]));
			memset(choice[i], -1, sizeof(choice[i]));
		}
		cin >> N >> W;
		for (auto i = 0; i < N; i++) {
			cin >> name[i];
			cin >> pack[i][VOLUME];
			cin >> pack[i][DESPERATION];	
		}

		cout << dp( -1, W) << " ";
		getans(-1, W);
		cout << ans.size() << endl;
		for (int i = 0; i < ans.size(); i++)
			cout << name[ans[i]] << endl;
		ans.clear();
		
	}

}

