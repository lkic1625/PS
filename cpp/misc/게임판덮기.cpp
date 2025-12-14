#include<iostream>

using namespace std;



void dfs(const int& h, const int& w, const int& stack);
void isCover(const int&h, const int& w,const int& stack);

bool isWhite(const int & h, const int & w);
int C, i, j, H, W, counting = 0 , ans = 0;
char map[22][22];



int main() {


	cin >> C;

	while (C > 0) {

		cin >> H >> W;

		H++; W++;

		for (i = 1; i < H; i++) {
			for (j = 1; j < W; j++) {
				cin >> map[i][j];
				if (map[i][j] == '.') counting++;
			}
		}

		if (counting % 3) {
			cout << 0 << endl;
			counting = 0;
			for (i = 1; i < H; i++) {
				for (j = 1; j < W; j++) {
					map[i][j] = '#';

				}
			}
			continue;
		}

		dfs(1, 1, 0);
		cout << ans <<endl;

		ans = 0;
		counting = 0;
		for (i = 1; i < H; i++) {
			for (j = 1; j < W; j++) {
				map[i][j] = '#';
				
			}
			cout << endl;
		}
		C--;
	}


	return 0;

}

void dfs(const int& h, const int& w, const int& stack) {
	cout << stack;
	if (stack == counting / 3  ) {
		ans++;
		return;
	}
	
	for (int i = h; i < H; i++) {
		for (int j = w; j < W; j++) {
			if (map[i][j] == '.')
				isCover(i, j,stack);
		}
	}
}

int check_row[8] = { 0,-1,-1,0,0,1,1,0 };
int check_col[8] = { -1 , 0, 0, 1 ,1, 0, 0, -1 };


void isCover(const int & h, const int & w, const int& stack)
{

	for (int i = 0; i < 8; i += 2) {
		if (isWhite(h + check_row[i], w + check_col[i]) && isWhite(h + check_row[i + 1], w + check_col[i + 1])) {
			map[h + check_row[i]][w + check_col[i]] = map[h + check_row[i + 1]][w + check_col[i + 1]] = map[h][w] = '#';
			dfs(h, w, stack + 1);
			map[h + check_row[i]][w + check_col[i]] = map[h + check_row[i + 1]][w + check_col[i + 1]] = map[h][w] = '.';
			
		}
	}
	
}

bool isWhite(const int & h, const int & w) {
	return map[h][w] == '.';
}