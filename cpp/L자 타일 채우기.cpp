#include <string>
#include<algorithm>
#include <vector>
#include<iostream>
using namespace std;

vector<string> b;
int check_row[2][4] = { 0,1,0,-1,1,0,-1,0 };
int check_col[2][4] = { 1,0,-1,0,0,-1,0,1 };

int cache[47][47][4];

bool isEmpty(int y, int x) {
	return !(y < 0 || y > b.size() - 1 || x < 0 || x > b[y].size() - 1)
		&& b[y][x] == '.';
}

bool findPos(int& y, int& x) {
	for (int i = 0; i < b.size(); i++)
		for (int j = i % 2; j < b[i].size(); j += 2) {
			if (b[i][j] == '.') {
				y = i;
				x = j;
				return true;
			}
		}
	return false;
}

int solve(int py, int px,int pk) {
	/*cout << endl;
	for (auto v : b) {
		cout << endl;
		for (auto k : v)
			cout << k;
	}*/
	int ret = 0;
	int x = -1, y = -1;
	int count = 0;
	if (!findPos(y, x)) return 0;
	
	int temp;
	for (int k = 0; k < 4; k++) {
		if ((y - py > 1 || x - px > 2) && cache[y][x][k] != -1) {
			return cache[y][x][k];
		}
		if (isEmpty(y + check_row[0][k], x + check_col[0][k]) &&
			isEmpty(y + check_row[1][k], x + check_col[1][k]))
		{

			b[y][x] = 'R';
			b[y + check_row[0][k]][x + check_col[0][k]] = 'R';
			b[y + check_row[1][k]][x + check_col[1][k]] = 'R';

			temp = solve(y,x,k) + 1;
			if (ret < temp) {
				ret = temp;
				pk = k;
			}
			
			b[y][x] = '.';
			b[y + check_row[0][k]][x + check_col[0][k]] = '.';
			b[y + check_row[1][k]][x + check_col[1][k]] = '.';
		}
		else count++;


	}


	if (count != 0) {
		b[y][x] = '0';
		ret = max(ret, solve(y, x, 4));
		b[y][x] = '.';
	}

	if (cache[y][x][pk] == -1) cache[y][x][pk] = ret;

	return ret;
}
//핵심 소스코드의 설명을 주석으로 작성하면 평가에 큰 도움이 됩니다.
class Solution {
public:

	int solution(vector<string> board) {

		for (int i = 0; i < 47; i++)
			for (int j = 0; j < 47; j++)
				for (int k = 0; k < 4; k++)
					cache[i][j][k] = -1;
		b = board;

		int ans = solve(0, 0, 0);
		return ans;

	}
};





int main() {
	Solution s;
	vector<string> a = { "X.....XXX.XX..XXXXXXXXX...X.XX.XX....X",".XXXX..X..XXXXXXXX....XX.X.X.X.....XXX","....XX....X.XX..X.X...XX.X..XXXXXXX..X","XX.XXXXX.X.X..X..XX.XXX..XX...XXX.X..." };
	cout << s.solution(a);
}
