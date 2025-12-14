#include<iostream>
#include<vector>
#include<algorithm>
typedef long long ll;

using namespace std;

const int MAX = 300000 + 3;

struct Query {
    int l, r, a;
};

int N, M, O, Q, L, R, A, lo[MAX], hi[MAX], goals[MAX];
ll tree[MAX];
Query queries[MAX];
vector<int> planets[MAX], pbs[MAX];

void update(int x, int diff) {
    while (x <= M) {
        tree[x] += diff;
        x += (x & -x);
    }
}

ll sum(int x) {
    ll ret = 0;
    while (x > 0) {
        ret += tree[x];
        x -= x & -x;
    }

    return ret;
}

int main() {
    //FAST IO
    ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

    cin >> N >> M;
    for (int i = 1; i <= M; ++i) {
        cin >> O;
        planets[O].push_back(i);
    }

    for (int allied = 1; allied <= N; ++allied) {
        cin >> goals[allied];
    }

    cin >> Q;
    for (int i = 1; i <= Q; ++i) {
        cin >> L >> R >> A;
        queries[i] = { L, R, A };
    }

    fill(hi, hi + N + 2, Q + 1);
    fill(lo, lo + N + 2, 1);

    bool flag = true;
    while (flag) {
        fill(tree, tree + MAX, 0);

        for (int allied = 1; allied <= N; ++allied) {
            if (!planets[allied].empty() && lo[allied] < hi[allied]) {
                pbs[(lo[allied] + hi[allied]) / 2].push_back(allied);
            }
        }

        for (int i = 1; i <= Q; ++i) {
            auto [l, r, a] = queries[i];
            if (l <= r) {
                update(l, a);
                update(r + 1, -a);
            } else {
                update(l, a);
                update(1, a);
                update(r + 1, -a);
            }

            while (!pbs[i].empty()) {
                int allied = pbs[i].back();
                pbs[i].pop_back();

                ll collection = 0;
                for (auto planet : planets[allied]) {
                    collection += sum(planet);
                    if (collection >= goals[allied]) {
                        break;
                    }
                }

                if (goals[allied] <= collection) {
                    hi[allied] = i;
                } else {
                    lo[allied] = i + 1;
                }

                flag = false;
            }
        }
    }

    for (int allied = 1; allied <= N; ++allied) {
        bool NIE = lo[allied] == Q + 1;
        if (NIE) {
            cout << "NIE\n";
        } else {
            cout << lo[allied] << '\n';
        }
    }
}