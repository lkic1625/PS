#include<iostream>

using namespace std;

const int MAX = 10;

enum class Block : int {
	HASH_TAG = 0,
	DOT = 1,
};

class Rotatable {
	
public:
	virtual Rotatable rotate() = 0;
};

class Map {
	Block real_map[MAX + 2][MAX + 2];
	int h, w;

public:
	Map(int h, int w) : h(h), w(w) { }
};

class Lattice : Rotatable, Map {

public:
	Lattice(int h, int w) {
		
	}
    Rotatable rotate() override {
        return this;
	}
};

int H, W, T, R, C;

int dfs(Point bef, Point cur) {

}


int main() {
	cin >> T;
	while (T-- > 0) {
		cin >> H >> W >> R >> C;
		
		Map map(H, W);
		Lattice lattice(R, C);

		char block;
		for (int i = 0; i < H; i++) {
			for (int j = 0; j < W; j++) {
				cin >> block;
				map[i][j] = block == '#' 
					? (int) Block::HASH_TAG 
					: (int) Block::DOT;
			}
		}

		for (int i = 0; i < R; i++) {
			for (int j = 0; j < C; j++) {
				cin >> block;
				lattice[i][j] = block == '#'
					? (int)Block::HASH_TAG
					: (int)Block::DOT;
			}
		}
	}

}