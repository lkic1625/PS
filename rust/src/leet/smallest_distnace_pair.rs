impl Solution {
    pub fn smallest_distance_pair(mut nums: Vec<i32>, k: i32) -> i32 {
        nums.sort();
        let n = nums.len();
        let mut l = 0;
        let mut r =  nums.last().unwrap() - nums.first().unwrap();
        let mut result = 0;

        while l < r {
            let mid = (l + r) / 2;

            let mut counter = 0;
            let mut i = 0;
            let mut j = 1;
            while (j < n) {
                while nums[j] - nums[i] > mid {
                    i += 1;
                }
                counter += j - i;
                j += 1;
            }

            if counter < k as usize {
                l = mid + 1;
            } else {
                result += mid;
                r = mid - 1;
            }
        }

        result
    }
}