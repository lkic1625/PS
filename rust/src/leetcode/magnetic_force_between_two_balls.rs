// Magnetic Force Between Two Balls
// https://leetcode.com/problems/magnetic-force-between-two-balls/editorial/?envType=problem-list-v2&envId=at4qzqgr
// In the universe Earth C-137, Rick discovered a special form of magnetic force between two balls if they are put in his new invented basket. Rick has n empty baskets, the ith basket is at position[i], Morty has m balls and needs to distribute the balls into the baskets such that the minimum magnetic force between any two balls is maximum.
// Rick stated that magnetic force between two different balls at positions x and y is |x - y|.
// Given the integer array position and the integer m. Return the required force.

// Input: position = [1,2,3,4,7], m = 3
// Output: 3
// Explanation: Distributing the 3 balls into baskets 1, 4 and 7 will make the magnetic force between ball pairs [3, 3, 6]. The minimum magnetic force is 3. We cannot achieve a larger minimum magnetic force than 3.

// 이 문제 역시, binary search 로 풀 수 있는 영역인데, 기본적으로 Split Array Largest Sum 로 접근함. 근데 매우 느린 풀이로 보여서 다시 공부 예정임.
struct Solution;
impl Solution {
    pub fn max_distance(mut position: Vec<i32>, m: i32) -> i32 {
        position.sort();
        let mut min_diff = i32::MAX;
        let max_diff = position.last().unwrap() - position.first().unwrap();
        for i in 1..position.len() {
            min_diff = std::cmp::min(position[i] - position[i - 1], min_diff);
        }

        let mut left = min_diff;
        let mut right = max_diff;
        let mut ret = 0;
        while left <= right {
            let allowed_diff = (left + right) / 2;
            if Self::required_balls(&position, allowed_diff) >= m {
                left = allowed_diff + 1;
                ret = std::cmp::max(allowed_diff, ret);
            } else {
                right = allowed_diff - 1;
            }
        }

        ret
    }

    pub fn required_balls(position: &Vec<i32>, allowed_diff: i32) -> i32 {
        let mut ret = 1;
        let mut curr_idx = 0;
        for i in 1..position.len() {
            if allowed_diff <= position[i] - position[curr_idx] {
                ret += 1;
                curr_idx = i;
            }
        }

        ret
    }
}

#[cfg(test)]
mod tests {
    use super::Solution;

    #[test]
    fn test() {
        assert_eq!(
            Solution::max_distance(vec![5, 4, 3, 2, 1, 1000000000], 2),
            999999999
        )
    }
}
