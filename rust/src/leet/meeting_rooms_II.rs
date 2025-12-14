impl Solution {
    pub fn min_meeting_rooms(intervals: Vec<Vec<i32>>) -> i32 {
        let mut vec: Vec<(i32, bool)> = intervals.iter().enumerate().flat_map(|(i, row)| vec![(row[0], true), (row[1], false)]).collect();
        vec.sort_by(|lhs, rhs| lhs.cmp(&rhs));

        let mut counter = 0;
        let mut ret = 0;
        for time in vec.iter() {
            if time.1 == true {
                counter += 1;
                ret = std::cmp::max(ret, counter);

            } else {
                counter -= 1;
            }
        }

        ret
    }
}
