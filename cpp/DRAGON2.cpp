#include <iostream>
using namespace std;
int p, l, o, c;
int main() {
	cin >> c;
	for (; c--;) {
		cin >> p >> p >> l;
		int i = p - 1;
		while (++i < p + l)
			if (i % 3)
				cout << "FX YF"[i % 6 - 1];
			else {
				o = i / 3;
				while (o % 2 == 0)
					o /= 2;
				cout << "+-"[o % 4 / 2];
			}
		cout << endl;
	}
}