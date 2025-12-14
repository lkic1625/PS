#include<iostream>
#include<algorithm>

using namespace std;

struct Point {
	int x, y;
};

// boundary for NPE(Null Pointer Exception)
const int MAX_N = 100'000 + 1, MAX_POINT = 500'000 + 1;

int n, x, y;
int sum_of_x[MAX_POINT * 2];
int sum_of_y[MAX_POINT * 2];
Point points[MAX_N];

int main() {
	//FAST IO
	ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
	
	cin >> n;
	for (int i = 0; i < n; i++) {
		cin >> x >> y;
		points[i] = { x + MAX_POINT, y + MAX_POINT };
	}

	for (int i = 0; i < n; i++) {
		int cur = i, next = (i + 1) % n;
		if (points[cur].x == points[next].x) {
			int start_of_line = min(points[cur].y, points[next].y);
			int end_of_line = max(points[cur].y, points[next].y);
			
			sum_of_y[start_of_line] += 1;
			sum_of_y[end_of_line] -= 1;
		}
		else {
			int start_of_line = min(points[cur].x, points[next].x);
			int end_of_line = max(points[cur].x, points[next].x);

			sum_of_x[start_of_line] += 1;
			sum_of_x[end_of_line] -= 1;
		}
	}

	
	for (int i = 1; i < MAX_POINT * 2; i++) {
		sum_of_x[i] += sum_of_x[i - 1];
		sum_of_y[i] += sum_of_y[i - 1];
	}

	int answer = max(*max_element(sum_of_x, sum_of_x + MAX_POINT * 2), *max_element(sum_of_y, sum_of_y + MAX_POINT * 2));

	cout << answer;
}