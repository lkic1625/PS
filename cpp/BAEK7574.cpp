#include<iostream>
#include<algorithm>
#include<tuple>
#include<set>
#include<cstdlib>

using namespace std;

const int MAX = 100000 + 5, MAX_R = 10000, MAX_D = 1e6, MAX_COORD = 1e7 + 3 * MAX_D;

enum {
	X = 0,
	Y
};

//¿¬²É
struct Node {
	double x, y;
	int index;
};

int d, N, root[MAX];
double x, y, r;
Node sorted[2][MAX];

int find(int a) {
	if (root[a] == a) return a;
	return root[a] = find(root[a]);
}

void merge(int a, int b) {
	a = find(a);
	b = find(b);

	if(a != b) root[b] = a;
}

int main() {
	//FAST IO
	ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
	//init
	
	cin >> N >> r;
	for (int i = 1; i <= N; i++) {
		cin >> x >> y;
		//move coord to the center of rectangle(node)
		x = x + r / 2;
		y = y + r / 2;
		sorted[X][i] = { x, y, i };
		sorted[Y][i] = { y, x, i };
	}
	cin >> d;

	//init
	sort(sorted[X], sorted[X] + N + 1, [](const Node& lv, const Node& rv) {
		return (lv.x != rv.x) ? (lv.x < rv.x) : (lv.y < rv.y);
	});
	sort(sorted[Y], sorted[Y] + N + 1, [](const Node& lv, const Node& rv) {
		return (lv.x != rv.x) ? (lv.x < rv.x) : (lv.y < rv.y);
	});
	for (int i = 0; i <= N + 1; i++) {
		root[i] = i;
	}

	//prim algorithm
	for (int axis = 0; axis < 2; axis++) {
		int pointer = 1;
		set<tuple<int, int>> s;
		
		for (int i = 1; i <= N; i++) {
			Node cur = sorted[axis][i];
			for (int j = pointer; j < i; j++) {
				Node bef = sorted[axis][j];
				if (cur.x - bef.x > r) {
					s.erase({ bef.y, j });
				}
				else {
					pointer = j;
					break;
				}
			}
			auto it = s.lower_bound({ cur.y, N + 1 });
			if (it != s.end()) {
				auto [y, index] = *it;
				Node bef = sorted[axis][index];
				if (abs(cur.y - bef.y) <= r + d) {
					merge(bef.index, cur.index);
				}
			}
			if (it != s.begin()) {
				it--;
				auto [y, index] = *it;
				Node bef = sorted[axis][index];
				if (abs(cur.y - bef.y) <= r + d) {
					merge(bef.index, cur.index);
				}
			}

			s.insert({ cur.y, i });
		}
	}

	double ans = 0;
	for (int i = 1; i <= N; i++) {
		if (find(sorted[X][i].index) == find(sorted[X][1].index)) {
			ans = max(ans, sorted[X][i].x + sorted[X][i].y + r);
		}
	}
	cout << (int)ans << '\n';

}