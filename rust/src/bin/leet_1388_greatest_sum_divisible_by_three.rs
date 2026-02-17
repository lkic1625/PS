//! # Greatest Sum Divisible by Three
//!
//! - Platform: LeetCode
//! - Number: 1388
//! - Difficulty: Medium
//! - URL: https://leetcode.com/problems/greatest-sum-divisible-by-three/

// Given an integer array nums, return the maximum possible sum of elements of the array such that it is divisible by three.
//
// Example 1:
// Input: nums = [3,6,5,1,8]
// Output: 18
// Explanation: Pick numbers 3, 6, 1 and 8 their sum is 18 (maximum sum divisible by 3).

// Example 2:
// Input: nums = [4]
// Output: 0
// Explanation: Since 4 is not divisible by 3, do not pick any number.

// Example 3:
// Input: nums = [1,2,3,4,4]
// Output: 12
// Explanation: Pick numbers 1, 3, 4 and 4 their sum is 12 (maximum sum divisible by 3).
pub struct Solution;

impl Solution {
    pub fn max_sum_div_three(nums: Vec<i32>) -> i32 {
        // dp[3][n] =
        let mut dp = vec![vec![0; nums.len() + 1]; 3];

        // 
        for i in (0..nums.len()).rev() {
            for j in 0..3 {
                let val = nums[i] as usize;
                if dp[(val + j) % 3][i + 1] != 0 {
                    dp[i][j] = val + dp[(val + j) % 3][i + 1]
                }
            }
        }

        dp[(nums[0] % 3) as usize][0] as i32
    }
}

fn main() {
    // TODO: Add example test
    println!("Solution compiled successfully");
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn test_example_1() {
        assert_eq!(Solution::max_sum_div_three(vec![3, 6, 5, 1, 8]), 18);
    }

    #[test]
    fn test_example_2() {
        assert_eq!(Solution::max_sum_div_three(vec![4]), 0);
    }

    #[test]
    fn test_example_3() {
        assert_eq!(Solution::max_sum_div_three(vec![1, 2, 3, 4, 4]), 12);
    }
}
