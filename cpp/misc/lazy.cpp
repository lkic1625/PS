#include<iostream>
#define MAX 1000000
typedef long long ll;
using namespace std;

int N, M, K;
ll segment[4 * MAX], lazy[4 * MAX], a, b, c, d;

void update_lazy(int node, int left, int right) {
	if (lazy[node] == 0) return;
	segment[node] += (right - left + 1) * lazy[node];
	if (left != right) {
		lazy[node * 2] += lazy[node];
		lazy[node * 2 + 1] += lazy[node];
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
	return segment[node] = update(lo, hi, value, 2 * node, left, mid) + update(lo, hi, value, 2 * node + 1, mid + 1, right);

}

ll sum(int lo, int hi, int node, int left, int right) {
	update_lazy(node, left, right);
	if (right < lo || hi < left) {
		return 0;
	}
	if (lo <= left && right <= hi) {
		return segment[node];
	}

	int mid = (left + right) / 2;
	return sum(lo, hi, 2 * node, left, mid) + sum(lo, hi, 2 * node + 1, mid + 1, right);
}

int main() {
	
	scanf("%d %d %d", &N, &M, &K);
	for (int i = 1; i <= N; i++) {
		scanf("%lld", &a);
		update(i, i, a, 1, 1, N);
	}
	for (int i = 0; i < M + K; i++) {
		scanf("%lld", &a);
		if (a == 1) {
			scanf("%lld %lld %lld", &b, &c, &d);
			update(b, c, d, 1, 1, N);
		}
		else {
			scanf("%lld %lld", &b, &c);
			printf("%lld\n", sum(b, c, 1, 1, N));
		}
	}
}