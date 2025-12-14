impl Solution {
    pub fn length_of_lis(mut nums: Vec<i32>) -> i32 {
        let mut memo = vec![1; nums.len() + 1];
        for i in (0..nums.len()).rev() {
            for j in (i + 1)..nums.len() {
                if nums[i] < nums[j] {
                    memo[i] = cmp::max(memo[j] + 1, memo[i])
                }
            }
        }
        *memo.iter().max().unwrap()
    }
}

// #[cfg(test)]
// mod tests {
//     use crate::Solution;

//     #[test]
//     fn solus() {
//         assert_eq!(4, Solution::length_of_lis(vec![10, 9, 2, 5, 3, 7, 101, 18]));
//     }
// }
