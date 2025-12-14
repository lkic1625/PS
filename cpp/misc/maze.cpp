#include<iostream>
#include<vector>
#include<string>
using namespace std;

vector<string> map;
int T, test_case = 10;

bool dfs(int i, int j) {

	if (map[i][j] == '3') return true;
	if (map[i][j] == '1') return false;

	map[i][j] = '1';
	return dfs(i + 1, j) || dfs(i, j + 1) || dfs(i, j - 1) || dfs(i - 1, j);
}

int main() {
	int x, y;
	string temp;
	while (test_case-- > 0) {
		cin >> T;
		for (int i = 0; i < 16; i++) {
			cin >> temp;
			map.push_back(temp);
			for (int j = 0; j < 16; j++) {
				if (map[i][j] == '2') {
					y = i;
					x = j;
				}
			}
		}
		
		cout << "#" << T << " " << (int)dfs(y, x) << endl;
		map.clear();
	}
}