#include<iostream>
#include<algorithm>
#include<stack>
#include<vector>

using namespace std;

const long long MAX_N = 100'000 + 5, MAX_HEIGHT = 1'000'000, TIME_BOUND = MAX_N * MAX_HEIGHT;

long long N, K, height[MAX_N], ans, k;

int array[100000000000000];

struct Segment {
    int left, right, height, segmented;
};

int main() {
    //FAST I/O
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);
    cin >> N >> K;

    stack<Segment> st;
  
    for (int i = 0; i <= N; i++) {
        if (i != N) {
            cin >> height[i];
        }

        int left = i;
        int segmented = 0;
        bool isFirst = true;
        
        while (!st.empty() && st.top().height >= height[i]) {
            left = st.top().left;

            long long diff = st.top().height - height[i];
            if (diff > 0) {
                if (isFirst) {
                    isFirst = false;
                    k++;
                    segmented++;
                }
                k -= st.top().segmented;
            }
            else {
                segmented += st.top().segmented;
            }

            if (k == K) {
                cout << ans << endl;
                return 0;
            }
            ans += diff * (st.top().right - st.top().left + 1);
            st.pop();
        }

        st.push({ left, i, height[i], segmented });
    }
    cout << -1;

}