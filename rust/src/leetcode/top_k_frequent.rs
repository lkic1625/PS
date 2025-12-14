/*
Given an integer array nums and an integer k, return the k most frequent elements. You may return the answer in any order.

Example 1:
Input: nums = [1,1,1,2,2,3], k = 2
Output: [1,2]

Quickselect 으로 o(n) 시간에 풀 수 있고 top k 를 고르는 문제에서 자주 사용된다고는 하는데, naive solution 도 쉽게 통과함.
Quickselect 로 추가되는 아이디어는 top k 문제를 푸는데에 적절하지만, 구현 난이도가 있어서 실제 아이디어 적용 등에는 난이도가 있다고 판단하여 따로 찾아보진 않겠음.
*/

struct Solution;

impl Solution {
    pub fn top_k_frequent(nums: Vec<i32>, k: i32) -> Vec<i32> {
        let mut vec = (0..=20000)
            .enumerate()
            .map(|x| (0, x.0 as i32 - 10000))
            .collect::<Vec<(i32, i32)>>();
        for i in nums {
            vec[i as usize + 10000] = (vec[i as usize + 10000].0 + 1, vec[i as usize + 10000].1);
        }

        vec.sort_unstable();
        let mut ret = Vec::new();
        for i in 0..k {
            ret.push(vec[20000 - k as usize].1 as i32)
        }

        ret
    }
}
