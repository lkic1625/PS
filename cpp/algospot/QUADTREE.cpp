#include <iostream>
#include <string>
using namespace std;

int c;
string tmp;
int pointer;

string quad() {

	//for (int i = 0; i < str.length(); i++) {
	if (tmp[pointer] == 'x') {
		string str1 = quad();
		string str2 = quad();
		string str3 = quad();
		string str4 = quad();

		pointer++;

		return "x" + str3 + str4 + str1 + str2;
	}
	else {
		pointer++;
		//cout << tmp[pointer - 1] << endl;
		//cout << tmp[pointer - 1] + "" << endl;
		
		return tmp[pointer -1] + "";
	}

	//}
}

int main() {

	cin >> c;
	while (c--) {
		cin >> tmp;
		pointer = 0;
		cout << quad();
	}
	return 0;
}