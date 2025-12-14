#include<algorithm>
#include<map>
#include<queue>
#include<cstdio>
#include<cstring>
#include<cassert>
#include<iostream>
#include<string>
#include<vector>
using namespace std;

int C, N, M;
const int ALPHABETS = 26;
int toNumber(char ch) { return ch - 'A'; }

// 트라이의 한 노드를 나타내는 객체
struct TrieNode {
	TrieNode* children[ALPHABETS];
	// 현 위치에서 끝나는 문자열의 번호
	int terminal;

	// 이 노드에서 매칭이 실패했을 때 이 곳으로 가서 계속한다.
	// 이 노드에 대응되는 문자열의 접미사이면서 트라이에 포함된 최대 문자열.
	TrieNode* fail;
	// 이 노드가 방문되었을 때 등장하는 문자열들의 번호
	vector<int> output;

	TrieNode() : terminal(-1) {
		memset(children, 0, sizeof(children));
	}

	~TrieNode() {
		for (int i = 0; i < ALPHABETS; i++)
			if (children[i])
				delete children[i];
	}

	// 이 노드를 루트로 하는 트라이에 번호가 id 인 문자열 key 를 추가한다
	void insert(const char* key, int id) {
		// 문자열이 끝나면 terminal 만 참으로 바꾸고 종료
		if (*key == 0)
			terminal = id;
		else {
			int next = toNumber(*key);
			// 해당 자식 노드가 없다면 생성한다
			if (children[next] == NULL)
				children[next] = new TrieNode();
			// 해당 자식 노드로 재귀호출
			children[next]->insert(key + 1, id);
		}
	}

	TrieNode* find(const char* key) {
		if (*key == 0) return this;
		int next = toNumber(*key);
		if (children[next] == NULL) return NULL;
		return children[next]->find(key + 1);
	}
};

void computeFailFunc(TrieNode* root) {
	queue<TrieNode*> q;
	root->fail = root;
	q.push(root);
	while(!q.empty()) {
		TrieNode* here = q.front();
		q.pop();
		for (int edge = 0; edge < ALPHABETS; edge++) {
			TrieNode* child = here->children[edge];
			if (!child) continue;
			if (here == root) child->fail = root;
			else {
				TrieNode* t = here->fail;
				while (t != root && t->children[edge] == NULL) {
					t = t->fail;
				}
				if (t->children[edge]) t = t->children[edge];
				child->fail = t;
				child->output = child->fail->output;
				if (child->terminal != -1) child->output.push_back(child->terminal);
				q.push(child);
			}
		}
	}
}

int main() {
	
}