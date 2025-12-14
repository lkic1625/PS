/*

함정 설치
https://algospot.com/judge/problem/read/TRAPCARD

bipartite matching

input
입력의 첫 줄에는 테스트 케이스의 수 C (C <= 50) 가 주어집니다. 
각 테스트 케이스의 첫 줄에는 지하 기지의 크기 H, W (1 <= H,W <= 20) 이 주어집니다. 
그 후 H 줄에 각 W 글자로 지하 기지의 지도가 주어집니다. 
이 문자열에서 #는 벽으로 막힌 칸, .는 빈 칸을 나타냅니다.

output
각 테스트 케이스마다 우선 설치할 수 있는 함정의 최대 수를 출력하고, 그 후 함정의 위치를 포함한 지하 기지의 지도를 다시 출력합니다. 
함정을 설치할 빈 칸은 . 대신 ^ 로 표시하며, 함정을 설치하는 방법이 여러 개 있다면 그 중 아무 것이나 선택해도 됩니다.

*/

#include<iostream>
#include<vector>
#include<string>
#include<string.h>
#include<queue>

using namespace std;

const int SIZE_A = 10000 + 1, SIZE_B = 10000 + 1, HEIGHT = 20 + 2, WIDTH = 20 + 2;
const int SIZE = HEIGHT * WIDTH, SOURCE = SIZE, SINK = SIZE + 1;

int u, v;
int capacity[SIZE + 2][SIZE + 2], flow[SIZE + 2][SIZE + 2];

struct Node {
	int x;
	int y;
	int index;
	
};

int H, W, C;
int m, n;
int dx[4] = { 0 , 1, 0, -1 }, dy[4] = { -1, 0, 1, 0 };
int adj[SIZE_A][SIZE_B];
string map[HEIGHT], input, boundary = "#####################";
Node node[SIZE_A][SIZE_B];
vector<int> match;
vector<bool> visited;


int dfs(int a) {
	if (visited[a]) return false;
	visited[a] = true;
	for (int b = 0; b < m; b++) {
		if (adj[a][b] && (match[b] == -1 || dfs(match[b]))) {
			match[b] = a;
		//	cout << a << " 와 " << b << "매칭" << endl;
			return true;
		}
	}

}
int bipartiteMatching() {
	//처음에는 정점이 모두 연결되어 있지 않음.

	match = vector<int>(m, -1);
	int size = 0;
	for (int start = 0; start < n; start++) {
		visited = vector<bool>(n, false);
		if (dfs(start))
			++size;
	}
	return size;
}


int main() {
	ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
	
	cin >> C;
	while (C-- > 0) {
		memset(adj, -1, sizeof(adj));
		memset(capacity, 0, sizeof(capacity));

		cin >> H >> W;
		map[0] = map[H + 1] = boundary;
		for (int i = 1; i <= H; i++) {
			cin >> input;
			input = "#" + input + "#";
			map[i] = input;
		}

		n = m = 0;
		for (int i = 1; i <= H; i++) {
			for (int j = 1; j <= W; j++) {
				if(map[i][j] == '.'){
					if ((i + j) % 2)
						node[i][j] = { j, i, m++ };
					else
						node[i][j] = { j, i, n++ };
				}
			}
		}

		for (int y = 1; y <= H; y++) {
			for (int x = 1; x <= W; x++) {
				if ((y + x) % 2 || map[y][x] != '.') continue;
				for (int i = 0; i < 4; i++) {
					int cy = y + dy[i], cx = x + dx[i];
					int A = node[y][x].index, B = node[cy][cx].index;
					if (map[cy][cx] == '.') {
						adj[A][B] = 1;
						capacity[SOURCE][A]++;
						capacity[A][B]++;
						capacity[B][SINK]++;
					}
				}
				
			}
		}

		int Answer = bipartiteMatching();
		cout << Answer << "\n";

	}
}