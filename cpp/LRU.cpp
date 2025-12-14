#include<iostream>
#include<set>
#include<time.h>
#include<vector>
#include<queue>
using namespace std;

const int LENGTH = 1000;//sequence 길이
const double RATE = 0.1;//sequence 길이, 작업 개수 비율
const int SIZE = LENGTH * RATE;//작업 개수
int seq[LENGTH];//work sequence
int way = 20;

int LRU(int *ref, int size, int way) {
	auto start = clock();
	vector<int> LRUstack, hit;
	for (int i = 0; i < size; i++) {
		for (auto iter = LRUstack.begin(); iter != LRUstack.end();) {
			if (*iter == ref[i]) {//when cache hit
				hit.push_back(ref[i]);
				iter = LRUstack.erase(iter);
			}
			else {
				iter++;
			}
		}
		LRUstack.push_back(ref[i]);
		if (LRUstack.size() > way) {
			LRUstack.erase(LRUstack.begin());
		}
	}
	auto end = clock();
	cout << hit.size() << " " << end - start << "\n";

	return hit.size();
}

void runLRU() {
	for (int i = 0; i < 100; i++) {
		for (int i = 0; i < LENGTH; i++) {
			seq[i] = rand() % SIZE;
		}
		LRU(seq, LENGTH, way);
	}

}

int main() {
	//environment variable init
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	srand((unsigned int)time(0));
	
	runLRU();
	
	
}