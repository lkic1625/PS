/**
 * Runtime: 417 ms, faster than 98.16% of C++ online submissions for Minimum Initial Energy to Finish Tasks.
 * Memory Usage: 93.3 MB, less than 81.25% of C++ online submissions for Minimum Initial Energy to Finish Tasks.
 */

#include <vector>
#include <algorithm>

using namespace std;

class Solution {
public:
    int minimumEffort(vector<vector<int>>& tasks) {
        sort(tasks.begin(), tasks.end(), [](const vector<int>& lv, const vector<int>& rv) -> bool {
            return lv[1] - lv[0] < rv[1] - rv[0];
        });

        int ans = 0;
        for (const auto &task: tasks) {
            ans = max(task[1], ans + task[0]);
        }

        return ans;
    }
};

