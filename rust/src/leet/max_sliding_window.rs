use std::collections::VecDeque;

struct Solution;

impl Solution {
    pub fn max_sliding_window(nums: Vec<i32>, k: i32) -> Vec<i32> {
        let k = k as usize;
        let mut ms: VecDeque<(usize, i32)>= VecDeque::new();
        let mut ret = Vec::with_capacity(nums.len() - k);

        for i in 0..nums.len() {
            if !ms.is_empty() {
                while !ms.is_empty() && ms.back().unwrap().1 < nums[i] {
                    ms.pop_back();
                }
            }
            ms.push_back((i, nums[i]));
            if i + 1 >= k {
                while ms.front().unwrap().0 + k <= i {
                    ms.pop_front();
                }
                ret.push(ms.front().unwrap().1);
            }
        }

        ret
    }
}
