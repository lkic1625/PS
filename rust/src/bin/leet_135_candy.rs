//! # Candy
//!
//! - Platform: LeetCode
//! - Number: 135
//! - Difficulty: Hard
//! - URL: https://leetcode.com/problems/candy/

// You are giving candies to these children subjected to the following requirements:

// Each child must have at least one candy.
// Children with a higher rating get more candies than their neighbors.
// Return the minimum number of candies you need to have to distribute the candies to the children.

// Example 1:
// Input: ratings = [1,0,2]
// Output: 5
// Explanation: You can allocate to the first, second and third child with 2, 1, 2 candies respectively.

// Example 2:
// Input: ratings = [1,2,2]
// Output: 4
// Explanation: You can allocate to the first, second and third child with 1, 2, 1 candies respectively.
// The third child gets 1 candy because it satisfies the above two conditions.?

pub struct Solution;

#[derive(PartialEq, Eq, Clone, Debug)]
pub enum Mode {
    MI,
    MD,
    EQUAL,
    NONE,
}

impl Solution {
    pub fn candy(ratings: Vec<i32>) -> i32 {
        let mut i = 0;
        let mut mode = Mode::NONE;
        let mut candy = 0;
        while i < ratings.len() {
            let mut bef = Mode::NONE;
            let mut length = 1;
            while i < ratings.len() - 1 && bef == mode {
                if ratings[i + 1] > ratings[i] {
                    mode = Mode::MI;
                } else if ratings[i + 1] < ratings[i] {
                    mode = Mode::MD;
                } else {
                    mode = Mode::EQUAL;
                }
                
                i += 1;
                if mode != Mode::EQUAL {
                    length += 1;
                    bef = mode;
                } else {
                    break;
                }
            }
            candy += ((length) * (length + 1)) / 2
        }

        candy
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
    fn test_example1() {
        // Input: ratings = [1,0,2]
        // Output: 5
        assert_eq!(Solution::candy(vec![1, 0, 2]), 5);
    }

    #[test]
    fn test_example2() {
        // Input: ratings = [1,2,2]
        // Output: 4
        assert_eq!(Solution::candy(vec![1, 2, 2]), 4);
    }
}
