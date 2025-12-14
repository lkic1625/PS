//
// Created by 조원빈 on 2021/08/10.
//

#include<iostream>
#include<algorithm>

using namespace std;

int N;
int A[1000 + 1];
int LIS[1000 + 1];
int LDS[1000 + 1];
int LBS[1000 + 1];

int main() {
    cin >> N;
    for(int i = 0; i < N; i++) {
        cin >> A[i];
    }

    for (int i = 0; i < N; i++) {
        LIS[i] = 1;
        for (int j = 0; j < i; j++) if (A[j] < A[i]) {
            LIS[i] = max(LIS[j] + 1, LIS[i]);
        }
    }

    for (int i = N - 1; i >= 0; i--) {
        LDS[i] = 1;
        for (int j = N - 1; j > i; j--) if (A[j] < A[i]) {
                LDS[i] = max(LDS[j] + 1, LDS[i]);
        }
    }

    for (int i = 0; i < N; i++) {
        LBS[i] = LIS[i] + LDS[i] - 1;
    }

    cout << *max_element(LBS, LBS + N);
    return 0;
}
