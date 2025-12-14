#include<iostream>
#include<queue>
#include<tuple>
using namespace std;

const int MAX = 500 + 2;

int H, W, h, i;
int map[MAX];
priority_queue<tuple<int, int>> pq;
//dijkstra algorithm

enum
{
	LEFT = -1,
	RIGHT = 1,
};

int traversal(int direction, int i) {
	int scope = 0;
	while (scope + i < W && scope + i > 0 && map[scope + i] == h) {
		scope += direction;
	}
	return scope + i;
}

int main() {

	//fast I/O
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	//input
	cin >> H >> W;
	for (int i = 1; i <= W; i++) {
		cin >> map[i];
		//init 
		pq.push({ -map[i], i });
	}
	int ans = 0;
	while (!pq.empty()) {
		//
		tie(h, i) = pq.top(); pq.pop();
		h = -h;
		//visited[i]? 
		if (map[i] != h) continue;

		//locate next node higher than current one.
		int left = traversal(LEFT, i);
		int right = traversal(RIGHT, i);
		int next = map[left] < map[right] ? left : right;

		if (map[next] > h) {
			//edge relaxation(update distance)
			for (int j = left + 1; j < right; j++) {
				map[j] = map[next];
				ans += map[next] - h;
			}
			pq.push({ -map[next], next });
		}
	}

	cout << ans;

}