#include<iostream>
#include<vector>
#include<algorithm>
#include<iomanip>
using namespace std;

enum Direction
{
	NORTH = 0,
	EAST,
	SOUTH,
	WEST
};
int N, M;
int map[8][8];
vector<int> cctv;

int watch(int y, int x, int direction);
void off(int y, int x, int direction);

int dfs(int depth) {

	
	if (depth == cctv.size()) return 0;

	int y = cctv[depth] / 10;
	int x = cctv[depth] % 10;
	int limit = 0;
	int ret = -1;


	switch (map[y][x])
	{
	case 1:
		for (int i = 0; i < 4; i++) {
			ret = max(ret, watch(y, x, i + NORTH) + dfs(depth + 1));
			off(y, x, i + NORTH);
		}
		break;
	case 2:
		for (int i = 0; i < 2; i++) {
			ret = max(ret, watch(y, x, i + NORTH) + watch(y, x, i + SOUTH) + dfs(depth + 1));
			off(y, x, i + NORTH);
			off(y, x, i + SOUTH);
		}
		break;
	case 3:
		for (int i = 0; i < 4; i++) {
			ret = max(ret, watch(y, x, i + NORTH)+ watch(y, x, i + EAST) + dfs(depth + 1));
			off(y, x, i + NORTH);
			off(y, x, i + EAST);
		}
		break;
	case 4:
		for (int i = 0; i < 4; i++) {
			ret = max(ret, watch(y, x, i + WEST)
				+ watch(y, x, i + NORTH) +
				watch(y, x, i + EAST) + dfs(depth + 1));
			
			off(y, x, i + WEST);
			off(y, x, i + NORTH);
			off(y, x, i + EAST);
		}
		break;
	case 5:
		for (int i = 0; i < 1; i++) {
		
			ret = max(ret, watch(y, x, i + WEST) + 
				watch(y, x, i + NORTH) +
				watch(y, x, i + EAST) +
				watch(y, x, i + SOUTH) + dfs(depth + 1));
			
			off(y, x, i + SOUTH);
			off(y, x, i + WEST);
			off(y, x, i + NORTH);
			off(y, x, i + EAST);
		}
		break;
	}

	return ret;

}

int main() {

	cin >> N >> M;
	int size = 0;
	for (int i = 0; i < N; i++)
		for (int j = 0; j < M; j++) {
			cin >> map[i][j];
			if (!map[i][j]) size++;
			else if (map[i][j] != 6) 
				cctv.push_back(i * 10 + j);
		}
	cout << size - dfs(0) << endl;

}

int watch(int y, int x, int direction) {
	direction %= 4;
	if (y < 0 || x < 0 || y > N - 1 || x > M - 1 || map[y][x] == 6) return 0;
	
	bool isMonitored = map[y][x] == 0;
	map[y][x] = map[y][x] <= 0 ? --map[y][x] : map[y][x];

	switch (direction)
	{
	case NORTH:
		return isMonitored + watch(y - 1, x, direction);
	case EAST:
		return isMonitored + watch(y, x + 1, direction);
	case SOUTH:
		return isMonitored + watch(y + 1, x, direction);
	case WEST:
		return isMonitored + watch(y, x - 1, direction);

	}
}

void off(int y, int x, int direction) {
	direction %= 4;
	if (y < 0 || x < 0 || y > N - 1 || x > M - 1 || map[y][x] == 6) return;
	
	map[y][x] = map[y][x] < 0 ? ++map[y][x] : map[y][x];
	switch (direction)
	{
	case NORTH:
		return off(y - 1, x, direction);
	case EAST:
		return off(y, x + 1, direction);
	case SOUTH:
		return off(y + 1, x, direction);
	case WEST:
		return off(y, x - 1, direction);

	}
}