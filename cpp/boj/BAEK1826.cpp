#include<iostream>
#include<algorithm>
#include<queue>

using namespace std;

const int MAX = 10000 + 5;

struct GasStation {
	int location, gas;
};

GasStation gas_station[MAX];
int N, L, P, a, b;

int main() {
	auto compare_by_location = [](GasStation lv, GasStation rv) {
		return lv.location < rv.location;
	};
	auto compare_by_gas = [](GasStation lv, GasStation rv) {
		return lv.gas < rv.gas;
	};

	cin >> N;
	for (int i = 0; i < N; i++) {
		cin >> a >> b;
		gas_station[i] = { a , b };
	}
	cin >> L >> P;
	sort(gas_station, gas_station + N, compare_by_location);

	priority_queue<GasStation, vector<GasStation>, decltype(compare_by_gas)> pq(compare_by_gas);

	int pivot = 0, location_of_truck = 0, ans = 0;
	for (pivot; pivot < N; pivot++) {
		if (gas_station[pivot].location > location_of_truck + P) {
			break;
		}
		pq.push(gas_station[pivot]);
	}

	while (!pq.empty()) {
		auto [location, gas] = pq.top(); pq.pop();
		P = P + gas - (location - location_of_truck);
		location_of_truck = location;
		ans++;
		if (location_of_truck + P >= L) {
			break;
		}
		for (pivot; pivot < N; pivot++) {
			if (gas_station[pivot].location > location_of_truck + P) {
				break;
			}
			pq.push(gas_station[pivot]);
		}
		
	}
	
	if (location_of_truck + P < L) {
		cout << -1;
	}
	else {
		cout << ans;
	}


}