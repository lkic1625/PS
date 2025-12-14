/*
https://www.algospot.com/judge/problem/read/MATCHFIX\

networkFlow, bellmanFord Algorithm

input
입력의 첫 줄에는 테스트 케이스의 수 C (C <= 50) 가 주어집니다.
각 테스트 케이스의 첫 줄에는 결승 리그에 참가하는 선수의 수 N (2 <= N <= 12) 과 남아 있는 경기의 수 M (0 <= M <= 100) 이 주어집니다. 
이 때 각 선수에게는 0부터 N-1 까지의 번호가 주어집니다. 
그 다음 줄에는 N 개의 정수로 0번부터 N-1 번까지 순서대로 각 선수의 현재 승수가 주어집니다. 
그 후 M 줄에는 각 경기를 치르는 두 선수의 번호가 주어집니다. 모든 선수의 현재 승수는 1000 이하입니다.

output
각 테스트 케이스마다 한 줄에 X가 리그를 단독 우승하기 위해 필요한 최소 승수를 출력합니다. 만약 이것이 불가능하다면 -1 을 출력합니다.

*/
#include<iostream>
#include<tuple>
#include<algorithm>
#include<string.h>
#include<queue>

using namespace std;

const int MAX_N = 12, MAX_M = 100, PLAYER_X = 0, SIZE = MAX_N + MAX_M, SOURCE = SIZE,  SINK = SIZE + 1;

int C, N, M, input, u, v;
int wins[MAX_N + 2], capacity[SIZE + 2][SIZE + 2], flow[SIZE + 2][SIZE + 2];
pair<int, int> match[MAX_M];

int FordFulkerson(int source, int sink) {
	//init flow edge
	memset(flow, 0, sizeof(flow));
	int totalFlow = 0;
	while (true) {
		vector<int> parent(SIZE + 2, -1);
		queue<int> q;
		parent[source] = source;
		q.push(source);
		while (!q.empty()) {
			int here = q.front(); q.pop();
			for (int there = 0; there < SIZE + 2; there++) {
				if (capacity[here][there] - flow[here][there] > 0
					&& parent[there] == -1) {//If there is a node that has not been visited and can flow, push to the queue.
					q.push(there);
					parent[there] = here;
				}
			}

		}
		if (parent[sink] == -1) break;
		int amount = MAX_N + 1;
		//finding the minimum amount of flow.
		for (int p = sink; p != source; p = parent[p]) {
			amount = min(amount, capacity[parent[p]][p] - flow[parent[p]][p]);
		}
		//flowing..
		for (int p = sink; p != source; p = parent[p]) {
			flow[parent[p]][p] += amount;
			flow[p][parent[p]] -= amount;
		}
		totalFlow += amount;
	}
	return totalFlow;

}


int isChampionshipable(int totalWins) {

	//If there is a Wins greater than totalWins, then return false;
	if (*max_element(wins  + 1, wins + N) >= totalWins) return false;
	//init capacity edge
	memset(capacity, 0, sizeof(capacity));
	//boundary of Indexing 
	int boundary = MAX_N;

	for (int i = 0; i < M; i++) {
		int u = match[i].first;
		int v = match[i].second;
		capacity[SOURCE][boundary + i] = 1;
		capacity[boundary + i][u] = 1;
		capacity[boundary + i][v] = 1;
	}
	
	//If X is to win alone with a w win, the win or loss of the remaining games will be properly determined 
	//and all other players must finish the league with less than w - 1 win.
	for (int node = 0; node < N; node++) {
		capacity[node][SINK] = max(totalWins - wins[node] - 1, 0);
	}
	capacity[PLAYER_X][SINK] = totalWins - wins[PLAYER_X];

	return FordFulkerson(SOURCE, SINK) == M && flow[PLAYER_X][SINK] == capacity[PLAYER_X][SINK];

}


int main() {
	//fast I/O
	ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

	//input
	cin >> C;
	while (C-- > 0) {
		int totalMatchCountOfX = 0;
		cin >> N >> M;
		for (int player = 0; player < N; player++) {
			cin >> input;
			wins[player] = input;
		}
		for (int game = 0; game < M; game++) {
			cin >> u >> v;
			match[game] = { u ,v };
			if (u == 0 || v == 0) {
				totalMatchCountOfX++;
			}
		}
		int flag = false, i = 0;
		for (; i <= totalMatchCountOfX; i++) {
			if (isChampionshipable(wins[PLAYER_X] + i)) {
				flag = true;
				break;
			}
		}
		if(flag)
			cout << i + wins[PLAYER_X] << "\n";
		else
			cout << -1 << "\n";

	}
	return 0;


}
