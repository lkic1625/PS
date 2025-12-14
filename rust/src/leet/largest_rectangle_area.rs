impl Solution {
    pub fn largest_rectangle_area(heights: Vec<i32>) -> i32 {
        let mut stack: Vec<(i32, i32)> = Vec::new();
        stack.push((-1, 0));
        let mut ret = 0;

        for (i, &val) in heights.iter().enumerate() {
            while stack.len() > 1 && stack.last().unwrap().1 >= val {
                let popped = stack.pop().unwrap();
                ret = std::cmp::max(ret, (i as i32 - stack.last().unwrap().0 - 1) * popped.1);
            }
            stack.push((i as i32, val));
        }

        while stack.len() > 1 {
            let popped = stack.pop().unwrap();
            ret = std::cmp::max(ret, (heights.len() as i32 - stack.last().unwrap().0 - 1) * popped.1);
        }

        ret
    }
}
