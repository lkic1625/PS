#include<iostream>
#include<string>
#include<stack>
#include<queue>

using namespace std;

string input, parseStr;

//node's current location
int cur;

enum 
{
	SQUARE_BRACKETS = '[',
	//SQUARE_BRACKETS + 2 == ']'
	BRACKETS = '('
	//BRACKETS + 1 == ')'
};

//function call STACK
bool isBalance() {
	stack<int> s;
	s.push('[');

	for (auto bracket : parseStr) {
		if (s.empty()) return false;
		int top = s.top();

		if (bracket == SQUARE_BRACKETS || bracket == BRACKETS) {
			s.push(bracket);
		} 
		else if (bracket - top == 2 || bracket - top == 1) {
			s.pop();
		}
		else {
			return false;
		}
	}
	//if stack is not empty, is not balance
	return s.empty();
}

int main() {

	//FAST IO
	ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

	while (true) {

		//init
		parseStr = "";

		//input
		getline(cin, input);
		
		//exit flag
		if (input == ".") break;
		
		//iteration for parsing 
		for (auto iter : input) {
			if (iter == BRACKETS
				|| iter == BRACKETS + 1
				|| iter == SQUARE_BRACKETS
				|| iter == SQUARE_BRACKETS + 2)
			{
				parseStr += iter;
			}
		}

		parseStr += "]";
		
		//output
		//parse string that length == 0 is balance
		bool outputFlag = parseStr.size() == 0 || isBalance();
		cout << (outputFlag ? "yes" : "no") << '\n';
	}
	
}