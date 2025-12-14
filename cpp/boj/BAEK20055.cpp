#include<iostream>
#include<queue>

using namespace std;

const int MAX_N = 100 + 5;

int durability[MAX_N * 2], belt[MAX_N * 2];
int N, K, ascend, descend, stage;
queue<int> robot;

int main() {
	cin >> N >> K;

	int mod = 2 * N;
	ascend = 1, descend = N;
	for (int i = 1; i <= 2 * N; i++) {
		cin >> durability[i % mod];
	}


	while (true) {
		ascend = (ascend - 1) % mod;
		descend = (descend - 1) % mod;
		
		int size = robot.size();
		
		for (int i = 0; i < size; i++) {
			int position = robot.front(); robot.pop();
			int next = (position + 1) % mod;
			
			if (belt[next] == false && durability[next] > 0 && next != descend) {
				belt[next] = true;
				durability[next] -= 1;
				robot.push(next);
			}
			else if(position == descend) {
				belt[position] = false;
			}
			else {
				robot.push(position);
			}
			
		}
		
		if (belt[ascend] == false && durability[ascend] > 0) {
			belt[ascend] = true;
			durability[ascend] -= 1;
		}
		
		int broken = 0;
		for (int i = 0; i < 2 * N; i++) {
			if (durability[i] == 0) broken += 1;
		}
		
		if (broken >= K) {
			break;
		}

		stage += 1;

	}

}