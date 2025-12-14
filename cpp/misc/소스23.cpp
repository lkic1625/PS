#include<iostream>

#include<vector>


using namespace std;

int backtracking(int num, vector<int> addition_chain) {

	if (num == addition_chain.back()) {
		for (auto iter : addition_chain) {
			cout << iter;
		}
		return addition_chain.size();
	}

	for (int i = addition_chain.size() - 2; i > 0; i--) {
		for (int j = i + 1; j < addition_chain.size(); j++) {
			vector<int> temp = addition_chain;
			temp.push_back(addition_chain[i] + addition_chain[j]);
			backtracking(num, temp);
		}
	}
}


int main() {

}