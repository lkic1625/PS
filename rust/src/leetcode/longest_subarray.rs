use std::cmp::{self, Reverse};
use std::collections::BinaryHeap;
use std::usize::MAX;

// 시간 복잡도: O(nlongn)
// 특징: stale 값을 유지하면서 BinaryHeap 을 전개하는 게 특이함. 그만큼 크게 필요없는 값이라서, Dequeue 구성을 한다면 O(N) 솔루션도 가능함 
impl Solution {
    pub fn longest_subarray(nums: Vec<i32>, limit: i32) -> i32 {
        let mut bh: BinaryHeap<(i32, Reverse<usize>)> = BinaryHeap::new();
        let mut rbh: BinaryHeap<(Reverse<i32>, Reverse<usize>)> = BinaryHeap::new();

        let mut left = 0;
        let mut right = 0;
        let mut ret = 0;

        while right < nums.len() {
            let x = nums[right];
            bh.push((x, Reverse(right)));
            rbh.push((Reverse(x), Reverse(right)));

            let max = bh.peek().unwrap();
            let min = rbh.peek().unwrap();

            // 8, 2, 4, 7
            if max.0 - min.0 .0 > limit {
                if max.1 .0 == right {
                    loop {
                        if let Some(top) = rbh.peek() {
                            if max.0 - top.0 .0 <= limit {
                                break;
                            }
                            left = cmp::max(left, top.1 .0 + 1);
                            rbh.pop();
                        }
                    }
                } else {
                    loop {
                        if let Some(top) = bh.peek() {
                            if top.0 - min.0 .0 <= limit {
                                break;
                            }
                            left = cmp::max(left, top.1 .0 + 1);
                            bh.pop();
                        }
                    }
                }
            }
            ret = cmp::max(ret, right - left + 1);
            right += 1;
        }

        ret as i32
    }
}
