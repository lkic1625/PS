#include<iostream>
#include<set>
#include<tuple>
#include<queue>
#include<algorithm>

using namespace std;

struct Route {
	long long start, end;
	int index;
};

auto compare_length = [](const Route& lv, const Route& rv) {
	if (lv.end - lv.start == rv.end - rv.start)
		return lv.start < rv.start;
	return lv.end - lv.start > rv.end - rv.start;
};

auto compare_x = [](const Route& lv, const Route& rv) {
	if (lv.start == rv.start)
		return lv.end > rv.end;
	return lv.start < rv.start; 
};

auto compare_index = [](const Route& lv, const Route& rv) {
	return lv.index < rv.index;
};

const int MAX_M = 500000 + 5, MAX_N = 1e9;
long long a, b, maxCircularEndpoint;
int N, M, isCanceled[MAX_M];
Route bus[MAX_M];
//set<Route, decltype(compare_length)> sorted_by_length(compare_length);
//set<Route, decltype(compare_x)> sorted_by_x(compare_x);

int main() {
	//FAST IO
	ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
	
	cin >> N >> M;
	for (int i = 0; i < M; i++) {
		cin >> a >> b;
		//bus route is a circle
		if (a > b) {
			maxCircularEndpoint = max(maxCircularEndpoint, b);
			bus[i] = { a, b + N, i + 1 };
			
			//sorted_by_length.insert({ a, b + N, i });
			//sorted_by_x.insert({ a, b + N, i });
		}
		else {
			bus[i] = { a, b, i + 1 };
			//sorted_by_length.insert({ a, b, i });
			//sorted_by_x.insert({ a, b, i });
			//sorted_by_x.insert({ a + N, b + N, i });
		}
		
	}
	//풀이1: 길이 순으로 버스좌표를 정렬 후 큰 것부터 본다면 최적인가?
	//풀이2: start 좌표로 정렬 후 라인스위핑 해가며 가장 최근으로 본 end 값보다 작은 end인 경우 삭제, 넘어가는 것도 삭제해야 함  
	//주석으로 감싸진 부분은 풀이 1임.

	sort(bus, bus + M, compare_x);
	deque<Route> ans;
	for (int i = 0; i < M; i++) {
		if (ans.empty() || ans.back().end < bus[i].end) {
			ans.push_back(bus[i]);
		}
	}
	while (!ans.empty() && ans.front().end <= maxCircularEndpoint) {
		ans.pop_front();
	}
	sort(ans.begin(), ans.end(), compare_index);
	for (auto& route : ans) {
		cout << route.index << ' ';
	}


	/*
	for (auto& route : sorted_by_length) {
		auto [start, end, index] = route;

		if (isCanceled[index]) continue;

		for (auto iter = sorted_by_x.lower_bound( { start, -1, 0 }); iter != sorted_by_x.end();) {
			auto [nextStart, nextEnd, nextIndex] = *iter;

			//If out of range
			if (nextStart >= end) break;

			//If we can delete this path
			if (nextEnd <= end && index != nextIndex) {
				iter = sorted_by_x.erase(iter);
				isCanceled[nextIndex] = true; 
			}
			else {
				iter++;
			}
		}
	}
	

	for (int i = 1; i <= M; i++) {
		if (isCanceled[i]) continue;
		cout << i << " ";
	}
	*/
}