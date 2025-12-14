#include<iostream>
#include<algorithm>
#include<vector>

typedef long long ll;

using namespace std;

const ll MAX = 500'000 + 5, MIN = -MAX * MAX;

struct Market {
	int t, l, m;
};

struct SegmentTree {
	vector<ll> tree;
	int dollors, n;

	SegmentTree(int dollors, int n) : dollors(dollors), n(n) {
		tree.assign(4 * n, MIN);
	}

	void _update(int index, int value, int node, int left, int right) {
		if (index < left || index > right) return;
		if (left == right) {
			tree[node] = value;
			return;
		}
		
		int mid = (left + right) / 2;
		_update(index, value, node * 2, left, mid);
		_update(index, value, node * 2 + 1, mid + 1, right);
		tree[node] = max(tree[node * 2], tree[node * 2 + 1]);
	}

	ll _query(int lo, int hi, int node, int left, int right) {
		if (left > hi or right < lo) {
			return MIN;
		}
		if (lo <= left and right <= hi) {
			return tree[node];
		}

		int mid = (left + right) / 2;
		return max(_query(lo, hi, node * 2, left, mid), _query(lo, hi, node * 2 + 1, mid + 1, right));
	}

	void update(int index, int value) {
		_update(index, value, 1, 1, n + 2);
	}

	int query(int lo, int hi) {
		return _query(lo, hi, 1, 1, n + 2);
	}
};

int N, U, D, S;
int T, L, M;

int locationToTime[MAX], timeToLocation[MAX], dp[MAX];
Market markets[MAX];


int main() {

	//FAST IO
	ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

	//init by inputs
	cin >> N >> U >> D >> S;
	auto up = SegmentTree(U, N + 2), down = SegmentTree(D, N + 2);
	
	markets[1] = { 0, S, 0 }; //start point
	locationToTime[1] = 1;
	for (int i = 2; i <= N + 1; i++) {
		locationToTime[i] = i;
		cin >> markets[i].t >> markets[i].l >> markets[i].m;
	}
	markets[N + 2] = { MAX, S, 0 }; //end point
	
	
	sort(markets + 1, markets + N + 2, [](const Market& lv, const Market& rv) {
		return lv.t == rv.t ? lv.l < rv.l : lv.t < rv.t;
	});

	sort(locationToTime + 1, locationToTime + N + 2, [](const int& lv, const int& rv) {
		return markets[lv].l < markets[rv].l;
	});

	for (int i = 1; i <= N + 1; i++) {
		timeToLocation[locationToTime[i]] = i;
	}
	
	//dp
	for (int i = 1; i <= N + 2; i++) {
		int pivot = timeToLocation[i];
		if (i == N + 2) {
			pivot = timeToLocation[1];
		}
		
		dp[i] = max(up.query(pivot + 1, N + 2) + U * markets[i].l, down.query(1, pivot) - D * markets[i].l) + markets[i].m;
		if (i == 1) {
			dp[i] = 0;
		}
		up.update(pivot, dp[i] - U * markets[i].l);
		down.update(pivot, dp[i] + D * markets[i].l);
	}

	cout << dp[N + 2] << endl;
}
