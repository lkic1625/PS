#include<iostream>
#include<algorithm>
#include<string>
using namespace std;

enum DragonCurve
{
	PFX,//+FX
	PYF,//+YF
	NFX,//-FX
	NYF //-YF
};
inline bool isX(int type) { return type % 2; }
inline bool isPositive(int type) { return type < 2; }
const string curve[4] = { "+FX", "+YF", "-FX", "-YF" };
const long long INF = 1000000000 + 50 + 1; //p <= 1000000000, l <= 50
long long cache[51] = { 3, }; //0th generation length : 3
int C, n, p, l;//input variable

//dp function
void generate(int n, int p, int l, int type) {
	if (n == 0) {//basis case
		printf("%s", curve[type].substr(p, l).c_str());
		return;
	}

	if (p + l <= cache[n - 1]) {
		generate(n - 1, p, l, isPositive(type) ? PFX : NFX);
	}
	else if(p < cache[n - 1] && cache[n - 1] < p + l){
		generate(n - 1, p, cache[n - 1] - p, isPositive(type) ? PFX : NFX);
		generate(n - 1, 0, l + p - cache[n - 1], isX(type) ? NYF : PYF);
	}
	else if (cache[n - 1] <= p) {
		generate(n - 1, p - cache[n - 1], l, isX(type) ? NYF : PYF);
	}

	return;
}

int main() {
	//memoization
	for (int i = 1; i < 51; i++)
		cache[i] = min(INF, cache[i - 1] * 2);

	cin >> C;
	while (C-- > 0) {
		cin >> n >> p >> l;
		generate(n, p, l, PFX);
		cout << endl;
	}
}