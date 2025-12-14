impl Solution {
    pub fn single_non_duplicate(nums: Vec<i32>) -> i32 {
        if nums.len() == 1 {
            return nums[0];
        }

        let mut left = 0;
        let mut right = nums.len() - 1;

        while left < right {
            let idx = (left + right) / 2;
            if nums[idx] == nums[idx + 1]  {

            } else {

            }
        }

        nums[left]
    }
}