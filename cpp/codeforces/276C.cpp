#include<iostream>
#include<set>
#include<algorithm>
#define MAX 200001
typedef long long ll;
using namespace std;

ll segment[4 * MAX], lazy[4 * MAX], a[MAX], b[MAX];
int n, q, l, r, input;
ll ans = 0;
inline bool cmp(ll& lv, ll& rv) { return lv > rv; }

void update_lazy(int node, int left, int right) {
	if (lazy[node] == 0) return;

	segment[node] += lazy[node] * (right - left + 1);
	if (left != right) {
		lazy[2 * node] += lazy[node];
		lazy[2 * node + 1] += lazy[node];
	}
	lazy[node] = 0;
}

ll update(int lo, int hi, ll value, int node, int left, int right) {
	update_lazy(node, left, right);
	if (right < lo || hi < left) {
		return segment[node];
	}
	if (lo <= left && right <= hi) {
		lazy[node] += value;
		update_lazy(node, left, right);
		return segment[node];
	}

	int mid = (left + right) / 2;
	return segment[node] = update(lo, hi, value, 2 * node, left, mid)
		+ update(lo, hi, value, 2 * node + 1, mid + 1, right);
}

ll query(int lo, int hi, int node, int left, int right) {
	update_lazy(node, left, right);
	if (right < lo || hi < left) {
		return 0;
	}
	if (lo <= left && right <= hi) {
		return segment[node];
	}
	int mid = (left + right) / 2;
	return query(lo, hi, 2 * node, left, mid) 
		+ query(lo, hi, 2 * node + 1, mid + 1, right);

}

int main() {
	cin >> n >> q;
	for (int i = 0; i < n; i++) {
		scanf("%d", &a[i]);
	}
	for (int i = 0; i < q; i++) {
		scanf("%d %d", &l, &r);
		update(l, r, 1, 1, 1, n);	
	}
	for (int i = 1; i < n + 1; i++) {
		b[i] = query(i, i, 1, 1, n);
	}
	sort(a, a + n + 1, cmp);
	sort(b, b + n + 1, cmp);
	for (int i = 0; i < n; i++) {
		ans += a[i] * b[i];
	}
	cout << ans;
	
}

