#include<iostream>

using namespace std;

int map[12][12];
int col[12];
int T;

int draw(int i2, int j2, int type) {
	int i = i2, j = j2;
	while (i != 11 && j != 11) map[i++][j++] += type;
	i = i2, j = j2;
	while (i != 0 && j != 0) map[i--][j--] += type;
	i = i2, j = j2;
	while (i != 11 && j != 0) map[i++][j--] += type;
	i = i2, j = j2;
	while (i != 0 && j != 11) map[i--][j++] += type;
	return type;
}

int nq(int n, int row) {
	if (row == n + 1) return 1;
	int ret = 0;
	for (int i = 1; i < n + 1; i++) {
		if (map[row][i] == 0 && col[i] == 0) {
			draw(row, i, 1);
			col[i] = 1;
			ret += nq(n, row + 1);    
			col[i] = 0;
			draw(row, i, -1);
		}
	}
	return ret;
}



int main() {
	
	int temp;
		cin >> temp;

		for (int i = 0; i < 12; i++) {
			col[i] = 0;
			for (int j = 0; j < 12; j++)
				map[i][j] = 0;
		}
		cout << nq(temp, 1) << endl;
	
}