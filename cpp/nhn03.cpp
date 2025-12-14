#include <iostream>
#include <sstream>
#include<string>
#include<regex>
#include<ctype.h>
#include <string.h>

using namespace std;

vector<string> cache;


bool is_integer(const std::string & s) {
	return std::regex_match(s, std::regex("[(-|+)|][0-9]+"));
}

string dfs(int iteration, int& idx, string order, string pelindrom = "") {
	string ret = "";

	while (idx < order.size() && order[idx] != ')') {

		if (isdigit(order[idx])) {
			int iter = order[idx] - '0';
			idx += 2;
			ret += dfs(iter, idx, order);
		}
		else if (order[idx] == '(') {
			idx += 1;
			
			string s = pelindrom;
			
			s.push_back(order[idx - 2]);
			ret.pop_back();
			ret += dfs(1, idx, order, s);
		}
		else {
			ret += pelindrom + order[idx];
			idx++;
		}


	}
	idx++;

	auto temp = ret;
	for (int i = 1; i < iteration; i++) {
		ret += temp;
	}

	return ret;

}

void solution(int numOfOrder, string *orderArr) {
	// TODO: 이곳에 코드를 작성하세요. 추가로 필요한 함수와 전역변수를 선언해서 사용하셔도 됩니다.
	for (int i = 0; i < numOfOrder; i++) {
		//cache.assign(20000 + 10, "");
		string ret = "";
		for (int j = 0; j < orderArr[i].size(); j++) {
			if (isdigit(orderArr[i][j])) {
				if (orderArr[i][j + 1] != '('){
					int iteration = orderArr[i][j] - '0';
					for (int k = 0; k < iteration; k++) {
						ret += orderArr[i][j + 1];
					}
					j++;
				}
				else {
					int iteration = orderArr[i][j] - '0';
					j += 2;
					ret += dfs(iteration, j, orderArr[i]);
				}
				
			}
			else if (orderArr[i][j] == '(') {
				j += 1;
				string s;
				
				s.push_back(orderArr[i][j - 2]);
				ret.pop_back();
				ret += dfs(1, j, orderArr[i], s);

			}
			else {
				ret += orderArr[i][j];
			}
		}
		cout << ret << '\n';
	}
	
}

struct input_data {
	int numOfOrder;
	string *orderArr;
};

void process_stdin(struct input_data& inputData) {
	string line;
	istringstream iss;

	getline(cin, line);
	iss.str(line);
	iss >> inputData.numOfOrder;

	inputData.orderArr = new string[inputData.numOfOrder];
	for (int i = 0; i < inputData.numOfOrder; i++) {
		getline(cin, line);
		iss.clear();
		iss.str(line);
		iss >> inputData.orderArr[i];
	}
}

int main() {
	struct input_data inputData;
	process_stdin(inputData);

	solution(inputData.numOfOrder, inputData.orderArr);
	return 0;
}