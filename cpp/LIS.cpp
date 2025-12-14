#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;

int N;

vector<int> A, s;
vector<vector<int> > ret;

int getIdx(int val) {
	return lower_bound(s.begin(), s.end(), val) - s.begin();
}

void solve() {
	int idx;

	for (int i = 0; i < A.size(); i++) {
		idx = getIdx(A[i]);
		if (idx == s.size()) 
			s.push_back(A[i]);	

		else 
			s[idx] = A[i]; 	
			
		ret[idx].push_back(A[i]);
	}
	
}
int main() {

	cin >> N;
	A.assign(N + 1,-1);
	ret.resize(N);	
	for (int i = 0; i < N; i++)
		cin >> A[i];

	solve();
	
	int idx = ret[s.size() - 1].size() - 1;
	A[s.size()] = 1000000001;
	cout << s.size() << endl;

	for (int i = s.size() - 1; i >= 0; i--) {	
		idx = 0;
		while (A[i + 1] <= ret[i][idx]) idx++;
		A[i] = ret[i][idx];
	}
	for (int i = 0; i < s.size(); i++)
		cout << A[i] << " ";
	
}