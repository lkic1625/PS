//swexpert 미생물 격리
//https://www.swexpertacademy.com/main/code/problem/problemDetail.do?contestProbId=AV597vbqAH0DFAVl&categoryId=AV597vbqAH0DFAVl&categoryType=CODE

#include<iostream>
#include<algorithm>
#include<vector>

#define UP 1
#define DOWN 2
#define LEFT 3
#define RIGHT 4

using namespace std;

int T, N, M, K;
int i, j, k;
int x2, y2, dir, num;
vector<int> area[100][100];

class MicCommu {
public:
	int dir;
	int num;
	int x, y;
	bool operator< (MicCommu const &r) {
		return this->num < r.num;
	}
	MicCommu() : num(0) {};
	MicCommu(int num, int dir, int x, int y) : num(num), dir(dir), x(x), y(y) {};
	void move() {
		switch (dir)
		{
		case UP:
			if (y > 0) y--;
			else {
				dir = DOWN;
				y++;
			}
			break;
		case DOWN:
			if (y < N - 1) y++;
			else {
				dir = UP;
				y--;
			}
			break;
		case LEFT:
			if (x > 0) x--;
			else {
				dir = RIGHT;
				x++;
			}
			break;
		case RIGHT:
			if (x < N - 1) x++;
			else {
				dir = LEFT;
				x--;
			}

			break;
		default:
			break;
		}
	}
};

vector<MicCommu> commu;

int solve(int m) {


	if (m == M) {
		int ret = 0;
		for (auto iter = commu.begin(); iter != commu.end(); iter++) ret += (*iter).num;
		return ret;
	}


	for (i = 0; i < commu.size(); i++) {
		if (commu[i].num == 0) continue;
		area[commu[i].y][commu[i].x].clear();
		commu[i].move();
		if (commu[i].y == 0 || commu[i].y == N - 1 || commu[i].x == 0 || commu[i].x == N - 1)
			commu[i].num /= 2;
	}
	for (i = 0; i < commu.size(); i++)
		area[commu[i].y][commu[i].x].push_back(i);


	for (i = 0; i < commu.size(); i++) {
		int m = -1, pos, sum = 0;
		if (area[commu[i].y][commu[i].x].size() > 1) {

			for (auto v : area[commu[i].y][commu[i].x]) {
				if (commu[v].num > m) {
					m = commu[v].num;
					pos = v;
				}
				sum += commu[v].num;
				commu[v].num = 0;
			}
			commu[pos].num = sum;
		}

	}


	return solve(m + 1);
}

int main() {
	cin >> T;
	int t = T;
	while (T-- > 0)
	{
		commu.clear();
		for (i = 0; i < 100; i++)
			for (j = 0; j < 100; j++)
				area[i][j].clear();

		cin >> N >> M >> K;
		commu.resize(K);
		for (i = 0; i < K; i++) {
			cin >> y2 >> x2 >> num >> dir;
			area[y2][x2].push_back(i);
			commu[i] = MicCommu(num, dir, x2, y2);
		}
		cout << "#" << t - T << " " << solve(0) << endl;
	}

}