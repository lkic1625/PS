#include <iostream>
#include <sstream>
#include<vector>
#include<map>
#include<string>

using namespace std;



void solution(int numOfAllPlayers, int numOfQuickPlayers, char *namesOfQuickPlayers, int numOfGames, int *numOfMovesPerGame) {
	// TODO: 이곳에 코드를 작성하세요. 추가로 필요한 함수와 전역변수를 선언해서 사용하셔도 됩니다.

	map<char, int> m;

	vector<char> players;
	players.assign(numOfAllPlayers - 1, 0);
	//init
	m.insert({ 'A', 0 });
	for (int i = 1; i < numOfAllPlayers; i++) {
		m.insert({ 'A' + i, 0 });
		players[i - 1] = 'A' + i;
	}
	
	int start = 0;//A
	char p = 'A';
	auto it = m.find(p);
	it->second = it->second + 1;
	for (int i = 0; i < numOfGames; i++) {
		int idx = (numOfMovesPerGame[i] + start + numOfAllPlayers - 1) % (numOfAllPlayers - 1);

		int flag = false;
		for (int j = 0; j < numOfQuickPlayers; j++) {
			if (namesOfQuickPlayers[j] == players[idx]) {
				flag = true;
			}
		}
		if (flag) {
			start = idx;
			
		}
		else {
			
			//swap
			int tempPlayerIdx = start;
			char tempPlayerName = p;

			start = idx;
			p = players[idx];
			players[idx] = tempPlayerName;
		}
		auto it = m.find(p);
		it->second = it->second + 1;
		
	}

	
	for (int i = 0; i < numOfAllPlayers - 1; i++) {
		auto it = m.find(players[i]);
		cout << players[i] << " " << it->second << '\n';
	}
	auto it2 = m.find(p);
	cout << p << " " << it2->second << '\n';

}

struct input_data {
	int numOfAllPlayers;
	int numOfQuickPlayers;
	char *namesOfQuickPlayers;
	int numOfGames;
	int *numOfMovesPerGame;
};

void process_stdin(struct input_data& inputData) {
	string line;
	istringstream iss;

	getline(cin, line);
	iss.str(line);
	iss >> inputData.numOfAllPlayers;

	getline(cin, line);
	iss.clear();
	iss.str(line);
	iss >> inputData.numOfQuickPlayers;

	getline(cin, line);
	iss.clear();
	iss.str(line);
	inputData.namesOfQuickPlayers = new char[inputData.numOfQuickPlayers];
	for (int i = 0; i < inputData.numOfQuickPlayers; i++) {
		iss >> inputData.namesOfQuickPlayers[i];
	}

	getline(cin, line);
	iss.clear();
	iss.str(line);
	iss >> inputData.numOfGames;

	getline(cin, line);
	iss.clear();
	iss.str(line);
	inputData.numOfMovesPerGame = new int[inputData.numOfGames];
	for (int i = 0; i < inputData.numOfGames; i++) {
		iss >> inputData.numOfMovesPerGame[i];
	}
}

int main() {
	struct input_data inputData;
	process_stdin(inputData);

	solution(inputData.numOfAllPlayers, inputData.numOfQuickPlayers, inputData.namesOfQuickPlayers, inputData.numOfGames, inputData.numOfMovesPerGame);
	return 0;
}