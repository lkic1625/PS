#include <algorithm>
#include <iostream>
#include <vector>
typedef long long ll;
using namespace std;

const int MAX = 1000000 + 3;

int N;
int sequence[MAX + 1], S[MAX + 1];
ll segment[MAX * 4];

// returns an index updated by
int updateTarget(int start, int end, int index, ll target) {
    segment[index]++;
    if (start == end) {
        return start;
    }

    int mid = (start + end) / 2;
    ll found = (mid - start + 1) - segment[index * 2];
    if (found < target) {
        return updateTarget(mid + 1, end, index * 2 + 1, target - found);
    } else {
        return updateTarget(start, mid, index * 2, target);
    }
}

int main() {
    //FAST IO
    ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);


    // input
    cin >> N;
    for (int i = 1; i <= N; i++) {
        cin >> sequence[i];
    }

    for (int i = 1; i <= N; ++i) {
        cin >> S[i];
    }


    sort(sequence + 1, sequence + N + 1);
    vector<int> answer;

    for (int i = N; i > 0; --i) {
        int picked = updateTarget(1, N, 1, S[i] + 1);
        answer.push_back(picked);
    }

    for (auto iter = answer.rbegin(); iter != answer.rend(); ++iter) {
        cout << sequence[*iter] << '\n';
    }
}
