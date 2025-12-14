#include<iostream>
#include<algorithm>

using namespace std;

const int MAX = 10000 + 2, MAX_COORD = 30000 + 5;

struct Coord {
	int x, y1, y2;
	bool is_endpoint;
};

Coord location[2 * MAX];
int X1, X2, Y1, Y2, N, is_overlap[4 * MAX_COORD];
long long seg[4 * MAX_COORD];

void update(int lo, int hi, bool is_endpoint, int node, int left, int right) {
    if (right < lo || hi < left) {
        return;
    }

    int val = is_endpoint ? -1 : 1;
    if (lo <= left && right <= hi) {
        is_overlap[node] += val;
    } else {
        int mid = (left + right) >> 1;
        update(lo, hi, is_endpoint, node * 2, left, mid);
        update(lo, hi, is_endpoint, node * 2 + 1, mid + 1, right);
    }

    if (is_overlap[node]) {
        seg[node] = right - left + 1;
        return;
    }

    if (left != right) {
        seg[node] = seg[node * 2] + seg[node * 2 + 1];
    } else {
        seg[node] = 0;
    }
}

int main() {
    // FAST IO
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

	cin >> N;
	for (int i = 0; i < N; ++i) {
		cin >> X1 >> Y1 >> X2 >> Y2;
		location[i] = { X1 ,Y1, Y2, false };
		location[i + N] = { X2, Y1, Y2, true };
	}

	//init
	sort(location, location + 2 * N, [](const Coord& lv, const Coord& rv) {
		return lv.x < rv.x;
	});
	update(location[0].y1, location[0].y2 - 1, location[0].is_endpoint, 1, 0, MAX_COORD - 1);
	int prev_x = location[0].x;
	long long ans = 0;

	for (int i = 1; i < 2 * N; ++i) {
	    // Decomposition declarations are a C++17 extension
		auto [x, y1, y2, isEndpoint] = location[i];
		long long width = x - prev_x;
		long long height = seg[1];

		ans += (width * height);
		update(y1, y2 - 1, isEndpoint, 1, 0, MAX_COORD - 1);
		prev_x = x;
	}

	cout << ans << '\n';
} 