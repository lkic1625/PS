#include<iostream>
#include<string.h>
#include<map>

using namespace std;

const int MAX_K = 30, MAX = 200 + 5;

struct Pointer{
	int y, x;
	
	int hashCode() {
		return y * MAX + x;
	}
}

int K, W, H;
int map[MAX][MAX];

vector<int> adj[MAX * MAX];

	
int bfs(Pointer u, Pointer v, int k) {
	
}

int main() {
	cin >> K;
	cin >> W >> H;
	memset(map, -1, sizeof map);
	
	for(int y = 1; y <= H; y++) {
		for(int x = 1; x <= W; x++) {
			cin >> map[y][x];
			if (map[y][x] == 0) {
				
			}
		}
	}
	
	
	
	
}