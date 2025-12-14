#include<iostream>
#include<algorithm>
#include<queue>
#include<tuple>
#include<iomanip>

using namespace std;

const int MAX = 1000 + 2;
int dy[4] = { -1, 0, 1, 0 };
int dx[4] = { 0, 1, 0, -1 };

int N, H, M, h;
int hole[MAX][MAX][4], tank[MAX][MAX], visited[MAX][MAX];
priority_queue<tuple<int, int, int>> pq;

auto isOuterWall = [](int x, int y) {
	return x < 1 || y < 1 || x > M || y > N;
};

int main() {

	//FAST IO
	ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

	//input
	cin >> N >> M >> H;
	for (int i = 1; i <= N + 1; i++) {
		for (int j = 1; j <= M; j++) {
			cin >> h;
			hole[i - 1][j][2] = h;
			hole[i][j][0] = h;
		}
	}
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= M + 1; j++) {
			cin >> h;
			hole[i][j - 1][1] = h;
			hole[i][j][3] = h;
		}
	}
	//fill the tank with water as much as possible.
	for (int y = 1; y <= N; y++) {
		for (int x = 1; x <= M; x++) {
			//get water that can be filled.
			int height = H;
			for (int i = 0; i < 4; i++) {
				int next_x = x + dx[i], next_y = y + dy[i];
				if (isOuterWall(next_x, next_y) && hole[y][x][i] != -1) {
					height = min(height, hole[y][x][i]);
				}
				
			}
			tank[y][x] = height;
			//dist init
			pq.push({ -tank[y][x], x, y });
		}
	}

	//Dijkstra algorithm
	while (!pq.empty()) {
		
		auto[h, x, y] = pq.top(); pq.pop();
		if (visited[y][x]) continue;
		visited[y][x] = true;
		
		for (int i = 0; i < 4; i++) {
			int next_x = x + dx[i], next_y = y + dy[i];
			if (!isOuterWall(next_x, next_y) && hole[y][x][i] != -1) {
				//update dist of neighbor nodes
				//in other words, update the water height.
				int dist = max(tank[y][x], min(hole[y][x][i], tank[next_y][next_x]));

				tank[y][x] = min(tank[y][x], max(hole[y][x][i], tank[next_y][next_x]));
				//If the height has changed, push to the queue
				if (dist < tank[next_y][next_x]) {
					tank[next_y][next_x] = dist;
					pq.push({ -tank[next_y][next_x], next_x, next_y });
				}
			}
		}
		
	}
	int ans = 0;
	//sum
	for (int y = 1; y <= N; y++) {
		for (int x = 1; x <= M; x++) {
			//cout << tank[y][x] << " ";
			ans += tank[y][x];
		}
		//cout << "\n";
	}

	cout << ans;


}