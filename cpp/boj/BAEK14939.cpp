#include<iostream>
#include<string>
#include<vector>
#include<algorithm>

#define XOR ^;


using namespace std;

const int SIZE = 10 + 2, MAX = SIZE * SIZE, OFF = 0;

int dx[5] = { 0, 1, 0, -1, 0 };
int dy[5] = { -1, 0, 1, 0, 0 };

string input;
vector<string> map, mirror_map;

inline int extract_element(int bit, int digit) {
	return bit & (1 << digit);
}

int string_to_bit(string str) {
	int ret = 0b0'000'000'000;
	for (int i = 0; i < str.size(); i++) {
		if (str[i] == 'O') ret |= (1 << i);
	}

	return ret;
}

void onoff(int y, int x) {
	
	for (int i = 0; i < 5; i++) {
		int next_y = y + dy[i];
		int next_x = x + dx[i];
		if (mirror_map[next_y][next_x] == '#') {
			mirror_map[next_y][next_x] = 'O';
		}
		else {
			mirror_map[next_y][next_x] = '#';
		}
	}
}

int traversal(int state, int row) {
	if (row == SIZE - 1) {
		return state == OFF ? 0 : MAX;
	}

	int switch_count = 0;
	for (int col = 1; col <= 10; col++) {
		int upper_bulb = extract_element(state, col - 1);

		if (upper_bulb != OFF) {
			switch_count += 1;
			onoff(row, col);
		}
	}
	//BOUND를 만들었기 때문에 substr 인자로 넣어줘야 함.
	int next_state = string_to_bit(mirror_map[row].substr(1, 10));

	return switch_count + traversal(next_state, row + 1);
}


int main() {

	//input and init to protect NullPointerException
	map.push_back("############");
	for (int i = 1; i <= 10; i++) {
		cin >> input;
		map.push_back('#' + input + '#');
	}
	map.push_back("############");

	int ans = MAX;
	/*전략
	왼쪽 위 전구부터 오른쪽 아래 방향으로 차례대로 전구를 킨다.	
	*/
	for (int bit = 0b0'000'000'000; bit < 0b10'000'000'000; bit++) {
		mirror_map.assign(map.begin(), map.end());
		ans = min(ans, traversal(bit, 1));
	}

	//ans 값이 변경되지 않았을 경우 정답이 없다.
	if (ans == MAX) {
		cout << -1;
	}
	else {
		cout << ans;
	}
}