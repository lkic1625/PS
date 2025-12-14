#include<iostream>
#include<vector>
#include<string>
#include<algorithm>
using namespace std;

int pos[4][4] = { {1,0,1,0}, {0,1,0,1}, {-1,0,-1,0}, {0,-1,0,-1} };
enum Direction
{
	UP,
	RIGHT,
	DOWN,
	LEFT
};
vector<string> map;
string temp;
int M, N;

int dfs(int ry, int rx, int by, int bx,int direction) {
	if(map[ry][rx] == '#' && map[by][bx] == '#')
	if (map[ry][rx] == 'O' && map[by][bx] != 'O') return 0;
	if (map[by][bx] == 'O') return 200;
	int ret = 10;
	int d = 1;
	while (map[ry + d][rx] == '.') {
		map[ry + d][rx] = '#';
		d++;
	}
	while (map[by + d][bx] == '.') {
		map[by + d][bx] = '#';
		d++;
	}
	
	
	
	

	return ret = ret == 10 ? -1 : ret;
}

int main() {
	cin >> N >> M;
	int rx, ry, bx, by;
	for (int i = 0; i < N; i++) {
		cin >> temp;
		map.push_back(temp);
		for (int j = 0; j < M; j++) {
			if (map[i][j] == 'R') {
				ry = i; rx = j;
			}
			if (map[i][j] == 'B') {
				by = i; bx = j;
			}
		}
	}
	cout << dfs(ry, rx, by, bx);
	
	


}