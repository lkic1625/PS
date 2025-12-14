
/// Given an integer array nums and an integer k, split nums into k non-empty subarrays such that the largest sum of any subarray is minimized.
/// Return the minimized largest sum of the split'.
/// A subarray is a contiguous part of the array.

// Input: nums = [7,2,5,10,8], k = 2
// Output: 18
// Explanation: There are four ways to split nums into two subarrays.
// The best way is to split it into [7,2,5] and [10,8], where the largest sum among the two subarrays is only 18.

/// bottom up 으로 하면 좀 더 빠를 수는 있는데, BS를 이용한 방법이 실제로 존재함.
/// 이 쪽 패턴은 처음 보는 거라 연습이 필요할 거 같음.
struct Solution;
impl Solution {
    
    
    pub fn split_array(nums: Vec<i32>, k: i32) -> i32 {
        let mut memo = vec![vec![-1; k as usize + 1]; nums.len()];
        let mut sum = vec![0; nums.len() + 1];
        for i in 1..=nums.len() {
            sum[i] = sum[i - 1] + nums[i - 1];
        }
        
        // sum[m] - sum[n] = [n, m)

        Self::dp(&sum, &mut memo, 0, k - 1)
    }

    pub fn dp(sum: &Vec<i32>, memo: &mut Vec<Vec<i32>>, n: usize, k: i32) -> i32 {
        if k == 0 {
            return sum[memo.len()] - sum[n];
        }

        if memo[n][k as usize] != -1 {
            return memo[n][k as usize];
        }

        let mut ret = i32::MAX;
        for i in (n + 1)..memo.len() {
            let sum = sum[i] - sum[n];
            let largest_min = Self::dp(sum, memo, i, k - 1);
            
            ret = cmp::min(
                cmp::max(sum, largest_min),
                ret
            );
            
            if sum > largest_min {
                break;
            }
        }

        memo[n][k as usize] = ret;
        ret
    }
}

#[cfg(test)]
mod tests {
    use crate::Solution;

    #[test]
    fn test() {
        assert_eq!(Solution::split_array(vec![7,2,5,10,8], 2), 18)
    }
}