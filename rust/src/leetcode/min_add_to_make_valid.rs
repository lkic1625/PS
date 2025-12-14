impl Solution {
    pub fn min_add_to_make_valid(mut s: String) -> i32 {
        let mut left: i32 = 0;
        let mut right: i32 = 0;
        for (_i, ch) in s.chars().enumerate() {
            if ch == '(' {
                left += 1
            } else if ch == ')' {
                if left > 0 {
                    left -= 1;
                } else {
                    right += 1;
                }
            }
        }
        left + right
    }
}
