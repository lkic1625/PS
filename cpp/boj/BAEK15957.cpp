#include<iostream>
#include<vector>
#include<algorithm>
#include<queue>

#include<map>
typedef long long ll; 

using namespace std;

const int MAX = 100000 + 2, MAX_VALUE = 1e+9, MAX_J = 1e+8, MAX_T = 1e9 + 1;

struct Query {
	int t, p, s;
};

struct Node {
	int parent, index, artist, descendants;
};

int N, K, T, P, S, parent, n, artist, order[MAX], lo[MAX], hi[MAX], answer[MAX];
ll seg[4 * MAX], lazy[4 * MAX], score[MAX], J;
Node tree[MAX];
Query queries[MAX];
vector<int> children[MAX], pbs[MAX], songs[MAX];


void update_lazy(int node, int left, int right) {
	if (lazy[node] == 0) return;
	seg[node] += (right - left + 1) * lazy[node];
	if (left != right) {
		lazy[node * 2] += lazy[node];
		lazy[node * 2 + 1] += lazy[node];
	}
	lazy[node] = 0;
}

ll update(int lo, int hi, ll value, int node, int left, int right) {
	update_lazy(node, left, right);
	if (right < lo || hi < left) {
		return seg[node];
	}
	if (lo <= left && right <= hi) {
		lazy[node] += value;
		update_lazy(node, left, right);
		return seg[node];
	}

	int mid = (left + right) / 2;
	return seg[node] = update(lo, hi, value, 2 * node, left, mid) + update(lo, hi, value, 2 * node + 1, mid + 1, right);
}

ll sum(int lo, int hi, int node, int left, int right) {
	update_lazy(node, left, right);
	if (right < lo || hi < left) {
		return 0;
	}
	if (lo <= left && right <= hi) {
		return seg[node];
	}

	int mid = (left + right) / 2;
	return sum(lo, hi, 2 * node, left, mid) + sum(lo, hi, 2 * node + 1, mid + 1, right);
}

int dfs(int cur) {
	order[cur] = ++n;
	tree[cur].index = n;
	for (auto child : children[cur]) {
		tree[cur].descendants += dfs(child);
	}
	return tree[cur].descendants + 1;
}

int main() {

	//FAST IO
	ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

	cin >> N >> K >> J;
	for (int i = 2; i <= N; i++) {
		cin >> parent;
		tree[i].parent = parent;
		children[parent].push_back(i);
	}
	for (int i = 1; i <= N; i++) {
		cin >> artist;
		songs[artist].push_back(i);
		tree[i].artist = artist;
	}

	for (int i = 0; i < K; i++) {
		cin >> T >> S >> P;
		queries[i] = { T, P, S };
	}
	sort(queries, queries + K, [](const Query& lv, const Query& rv) {
		return lv.t < rv.t;
	});

	dfs(1);

	fill(answer, answer + N + 1, MAX_T);
	fill(hi, hi + N + 1, K - 1);
	bool flag = true;

	while (flag) {
		
		fill(score, score + MAX, 0);
		fill(seg, seg + MAX * 4, 0);
		fill(lazy, lazy + MAX * 4, 0);

		for (int artist = 1; artist <= N; artist++) {
			if (songs[artist].size() && lo[artist] <= hi[artist]) {
				pbs[(lo[artist] + hi[artist]) / 2].push_back(artist);
			}
		}
		flag = false;
		for (int i = 0; i < K; i++) {
			auto [t, p, s] = queries[i];
			int root = order[s];
			int length = tree[s].descendants;
			update(root, root + length, p / (length + 1), 1, 1, N);

			while (!pbs[i].empty()) {
				int artist = pbs[i].back(); pbs[i].pop_back();
				
				for (auto song : songs[artist]) {
					int index = tree[song].index;
					score[artist] += sum(index, index, 1, 1, N);
					//if (score[artist] / songs[artist].size() > J) break;
				}

				ll target = J * songs[artist].size();
				if (target < score[artist]) {
					answer[artist] = min(answer[artist], queries[i].t);
					hi[artist] = i - 1;
				}
				else {
					lo[artist] = i + 1;
				}

				flag = true;
			}

		}


	}
	for (int i = 1; i <= N; i++) {
		int flag = answer[tree[i].artist] != MAX_T;
		cout << (flag ? answer[tree[i].artist] : -1) << '\n';
	}

	return 0;


}