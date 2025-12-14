#include<iostream>
#include<algorithm>
using namespace std;

int dx[6] = { 1, 0, -1, 0, 0, 0 };
int dy[6] = { 0, 1, 0, -1, 0, 0 };
int dz[6] = { 0, 0, 0, 0, 1, -1 };

int map[7][7][7];

int search(int i, int j, int k, int rotate) {
	if (i == 5 + rotate && j == 5 + rotate && k == 5 + rotate)
		return 0;
	map[i][j][k] = 2;
	int x, y, z;
	int ret = 0;
	bool retFlag = true;
	for (int l = 0; l < 6; l++) {
		z = i + dz[l]; y = j + dy[l]; x = k + dx[l];
		if (map[i + dz[l]][j + dy[l]][k + dx[l]] == 1) {
			ret = min(ret, 1 + search(z, y, x, rotate));
			retFlag = false;
		}
	}
	if (retFlag) return 1000000;
}

int main() {
	for (int i = 1; i < 6; i++) {//input code
		for (int j = 1; j < 6; j++) {
			for (int k = 1; k < 6; k++) {
				cin >> map[i][j][k];
			}
		}
	}

}