#include <string>
#include <vector>
#include<iostream>
#include<queue>
#include<tuple>
#include<map>
#include<set>

using namespace std;

map<int, set<int>> y_sorted_bomb, x_sorted_bomb, y_sorted_box, x_sorted_box;
map<tuple<int, int>, vector<tuple<int, int>>> cnt;
set<tuple<int, int >> m;

enum {
	UP = 0,
	DOWN,
};

void boxing(set<int>& coord, int direction, int x, int y, int K, int& k, bool flag) {
	auto it = flag ? coord.find(x) : coord.find(y);
	for (; it != coord.end() && (*it) <= x + K && (*it) >= x - K; ) {
		int n = (*it);
		k = min(k, abs(n - x));
		
		if (direction == UP) it++;
		else it--;
	}
}
void insertion(set<int>& coord, int direction, int x, int y, int K, int& k, bool flag) {
	auto it = flag ? coord.find(x) : coord.find(y);
	for (; it != coord.end() && (*it) <= x + k && (*it) >= x - k;) {
		int n = (*it);
		if (flag) {
			cnt[{y, x}].push_back({ y, n });
		}
		else {
			cnt[{y, x}].push_back({ n, x });
		}

		if (direction == UP) it++;
		else it--;
	}
}

int solution(vector<vector<int>> bomb, vector<vector<int>> box, int K) {
	int answer = 0;
	
	//init
	for (int y = 0; y < bomb.size(); y++) {
		for (auto x : bomb[y]) {
			m.insert({ y,  x });
			y_sorted_bomb[x].insert(y);
			x_sorted_bomb[y].insert(x);
		}	
	}

	for (int y = 0; y < box.size(); y++) {
		for (auto x : box[y]) {
			y_sorted_box[x].insert(y);
			x_sorted_box[y].insert(x);
		}	
	}
	
	for (int y = 0; y < bomb.size(); y++) {
		for (auto x : bomb[y]) {
			int k[4] = { K, K, K, K };
			//boxing
			auto coord_y = x_sorted_box[y];
			auto coord_x = y_sorted_box[x];
			boxing(coord_y, UP, x, y, K, k[0], true);
			boxing(coord_y, DOWN, x, y, K, k[1], true);
			boxing(coord_x, UP, x, y, K, k[2], false);
			boxing(coord_x, DOWN, x, y, K, k[3], false);

			coord_y = x_sorted_bomb[y];
			coord_x = y_sorted_bomb[x];

			insertion(coord_y, UP, x, y, K, k[0], true);
			insertion(coord_y, DOWN, x, y, K, k[1], true);
			insertion(coord_x, UP, x, y, K, k[2], false);
			insertion(coord_x, DOWN, x, y, K, k[3], false);

			/*for (auto it = coord_y.find(x); it != coord_y.end() && (*it) <= x + K; it++) {
				int nx = (*it);
				k[0] = min(k[0], abs(nx - x));
			}
			for (auto it = coord_y.find(x); it != coord_y.end() && (*it) >= x - K; it--) {
				int nx = (*it);
				k[1] = min(k[1], abs(nx - x));
			}
			
			for (auto it = coord_x.find(y); it != coord_x.end() && (*it) <= y + K; it++) {
				int ny = (*it);
				k[2] = min(k[2], abs(ny - y));
			}
			for (auto it = coord_x.find(y); it != coord_x.end() && (*it) >= y - K; it--) {
				int ny = (*it);
				k[3] = min(k[3], abs(ny - y));
			}
			
			for (auto it = coord_y.find(x); it != coord_y.end() && (*it) <= x + k[0]; it++) {
				int nx = (*it);
				cnt[{y, x}].push_back({ y, nx });
			}
			for (auto it = coord_y.find(x); it != coord_y.end() && (*it) >= x - k[1]; it--) {
				int nx = (*it);
				cnt[{y, x}].push_back({ y, nx });
			}
			
			for (auto it = coord_x.find(y); it != coord_x.end() && (*it) <= y + k[2]; it++) {
				int ny = (*it);
				cnt[{y, x}].push_back({ ny , x });
			}
			for (auto it = coord_x.find(y); it != coord_x.end() && (*it) >= y - k[3]; it--) {
				int ny = (*it);
				cnt[{y, x}].push_back({ ny , x });
			}*/
			
		}
		
	}

	//범위 확인 후 크기 순 정렬
	set<tuple<int, int, int>> s;
	for(auto iter : cnt) {
		auto[y, x] = iter.first;
		auto length = iter.second.size();
		s.insert({ length, y, x });
	}

	//큰 순서로 폭탄 확인(폭파)
	for (auto iter : s) {
		auto[l, y, x] = iter;
		auto isDeleted = m.find({ y, x }) == m.end();
		if (!isDeleted) answer++;
		for (auto it = cnt[{y, x}].begin(); it != cnt[{y, x}].end(); it++) {
			auto[ny, nx] = *it;
			auto bombs = m.find({ ny ,nx });
			if (bombs != m.end()) {
				m.erase(bombs);
			}
		}
	}
	return answer;
	
}

int main() {
	vector<int> a;
	vector<vector<int>> b = {
	{1, 4},
	{},
	{1},
	{4},
	{3, 6}
		

	};
	vector<vector<int>> c = { {}, {1}, {2} };
	
	cout << solution(b, c, 3);


}
