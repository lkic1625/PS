#include<queue>
#include<iostream>

using namespace std;

const int MAX_FLIP = 10, MAX_COIN = 100 + 3, MAX_BIT = (1 << MAX_FLIP) + 1, INIT = 10000;
int state_bit[MAX_COIN], target_bit[MAX_COIN], dist[MAX_COIN][MAX_BIT];
int N, K;

int flipAll(int bit) {
	for (int i = 0; i < K; i++) {
		bit ^= (1 << i);
	}
}


int main(){
	cin >> N >> K;
	for (int i = 0; i < N; i++) {
		cin >> state_bit[i];
	}
	for (int i = 0; i < N; i++) {
		cin >> target_bit[i];
	}
	for (int i = 0; i < N; i++) {
		target_bit[i] = state_bit[i] ^ target_bit[i];
	}
	memset(dist, INIT, sizeof dist);

	priority_queue<pair<int, pair<int, int>>> pq;
	pq.push({ 0, { 1, 0 } });
	dist[1][0] = 0;
	while (pq.empty() == false) {
		int flips = pq.top().first; // === dist
		auto [index, bit] = pq.top().second;
		pq.pop();
		if (flips > dist[index][bit]) continue;

		int last_bit = bit % 2;
		if (last_bit == target_bit[index] && index + K - 1 < N) {
			int next_bit = bit >> 1;
			if (dist[index + 1][next_bit] > dist[index][bit]) {
				dist[index + 1][next_bit] = dist[index][bit];
				pq.push({ -dist[index + 1][next_bit], {index + 1, next_bit} });
			}
		}

		int flip = flipAll(bit);
		for (int pivot = 0; pivot < K; pivot++) {
			int next_bit = flip ^ (1 << pivot);
			int last_bit = next_bit % 2;
			if (dist[index + 1][next_bit] > dist[index][bit]) {
				dist[index + 1][next_bit] = dist[index][bit];
				pq.push({ -dist[index + 1][next_bit], {index + 1, next_bit} });
			}

			if (target_bit[index] != last_bit || index + K - 1 == N) continue;

			if (dist[index + 1][next_bit >> 1] > dist[index][bit] + 1) {
				dist[index + 1][next_bit >> 1] = dist[index][bit] + 1;
				pq.push({ -dist[index + 1][next_bit >> 1], {index + 1, next_bit >> 1 } });
			}
		}
	}

}