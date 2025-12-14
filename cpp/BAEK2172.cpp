//
// Created by 조원빈 on 2021/08/02.
//

#include<iostream>
#include<vector>
#include<string.h>
#include<set>

using namespace std;

const int MAX = 20, NUMBER_OF_DIRECTION = 8;

// input variable
int N, L;
int map[MAX + 2][MAX + 2];
int dp[MAX + 2][MAX + 2][MAX + 2][MAX + 2][MAX + 2];

int dy[8] = {-1, -1, 0, 1, 1, 1, 0, -1};
int dx[8] = {0, 1, 1, 1, 0, -1, -1, -1};

int main() {

    // init
    cin >> N >> L;
    memset(map, -1, sizeof map);
    for (int i = 1; i <= N; i++) {
        for (int j = 1; j <= N; j++) {
            cin >> map[i][j];
        }
    }

    for (int y = 1; y <= N; ++y) {
        for (int x = 1; x <= N; ++x) {
            dp[1][y][x][y][x] = 1;
            for (int i = 0; i < NUMBER_OF_DIRECTION; i++) {
                int ny = dy[i] + y, nx = dx[i] + x;
                if (map[ny][nx] == map[y][x]) {
                    dp[2][ny][nx][y][x] = 1;
                    dp[2][y][x][ny][nx] = 1;
                }
            }
        }
    }

    for (int l = 3; l <= L; l++) {
        for (int y1 = 1; y1 <= N; ++y1) {
            for (int x1 = 1; x1 <= N; ++x1) {
                for (int y2 = 1; y2 <= N; ++y2) {
                    for (int x2 = 1; x2 <= N; ++x2) {
                        for (int i = 0; i < NUMBER_OF_DIRECTION; i++) {
                            for (int j = 0; j <NUMBER_OF_DIRECTION; j++) {
                                int ny1 = dy[i] + y1, nx1 = dx[i] + x1;
                                int ny2 = dy[j] + y2, nx2 = dx[j] + x2;

                                if (map[ny1][nx1] == map[ny2][nx2]) {
                                    dp[l][ny1][nx1][ny2][nx2] += dp[l - 2][y1][x1][y2][x2];
                                }
                            }
                        }
                    }
                }
            }
        }
    }

    int ret = 0;
    for (int y1 = 1; y1 <= N; ++y1) {
        for (int x1 = 1; x1 <= N; ++x1) {
            for (int y2 = 1; y2 <= N; ++y2) {
                for (int x2 = 1; x2 <= N; ++x2) {
                    ret += dp[L][y1][x1][y2][x2];
                }
            }
        }
    }

    cout << ret;
}