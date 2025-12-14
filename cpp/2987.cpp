#include<iostream>
#include<string>
using namespace std;

int T, N, M;
int F[1000000], A[500000];
string str;

void generate(int i, string str) {
	
}
	
void generate(int sub,int interval, int num, string str) {
	if (sub > 2 || sub < -2 || interval > 2|| interval < -2) return;
	if (num == 0) {
		M++;
		cout << str << endl;
		return;
	}
	if (interval > 0) {
		generate(sub + 1,interval + 1, num - 1, str + 'L');
		generate(sub - 1,-1, num - 1, str + 'P');
	}
	else if (interval < 0) {
		generate(sub + 1,1, num - 1, str + 'L');
		generate(sub - 1,interval - 1, num - 1, str + 'P');
	}
	else {
		generate(sub + 1,interval + 1, num - 1, str + 'L');
		generate(sub - 1,interval - 1, num - 1, str + 'P');
	}
}

int main() {
	cin >> T;
	
	while (T-- > 0) {
		cin >> N >> M;
		generate(0, 0, N, "");
		
	}
}