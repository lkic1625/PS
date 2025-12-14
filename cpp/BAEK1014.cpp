#include<iostream>
#include<vector>
#include<string>

using namespace std;

vector<string> map;
vector<string> mirror_map;

int C, N, M;
int dx[4] = { -1, 1, 1, -1 };
int dy[4] = { -1, -1, 0, 0 };
string input;

bool is_vulnerable(int y, int x, int bef, int cur) {
	for (int i = 0; i < 4; i++) {
		if (dy[i] == -1) {
			if (bef & (1 << x + dx[i] - 1)) return true;
		}
		else {
			if (cur & (1 << x + dx[i] - 1)) return true;
		}
	}

	return false;
}

int string_to_bit(string str) {
	int ret = 0;
	for (int i = 0; i < str.size(); i++) {
		if (str[i] == 'o') ret |= (1 << i);
	}

	return ret;
}

int dp(int state, int row) {
	int desk = 0;
	if (row == N + 1) {
		return 0;
	}

	for (int col = 1; col <= M; col++) {
		int current_state = string_to_bit(mirror_map[row].substr(1, M));
		if (is_vulnerable(row, col, state, current_state) || map[row][col] == 'x') {
			
		}
		else {
			desk += 1;
			mirror_map[row][col] = 'o';
		}
	}

	int next_state = string_to_bit(mirror_map[row].substr(1, M));
	return desk + dp(next_state, row + 1);
}


int main() {
	cin >> C;

	while (C-- > 0) {
		//input and init to protect NullPointerException
		map.clear();
		cin >> N >> M;
		map.push_back("xxxxxxxxxxx");
		for (int i = 0; i < N; i++) {
			cin >> input;
			map.push_back('x' + input + 'x');
		}
		map.push_back("xxxxxxxxxxxx");

		int ans = 0;
		for (int bit = 0; bit < (1 << M); bit++) {
			mirror_map.assign(map.begin(), map.end());
			ans = max(ans, dp(bit, 1));
		}

		cout << ans << endl;
	}
	
}