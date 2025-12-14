use std::cmp;
use std::cmp::Ordering;

struct Solution;

struct Item {
    idx: usize,
    val: i32,
}

impl Item {
    pub fn new(idx: usize, val: i32) -> Self {
        Item {
            idx,
            val
        }
    }
}

struct Range {
    l: i32,
    r: i32
}

impl Range {
    pub fn new(l: i32, r: i32) -> Self {
        Range {
            l,
            r
        }
    }
}

impl Eq for Range {}

impl PartialEq<Self> for Range {
    fn eq(&self, other: &Self) -> bool {
        let lhs = self.r - self.l;
        let rhs = other.r - other.l;

        lhs.eq(&rhs)
    }
}

impl PartialOrd<Self> for Range {
    fn partial_cmp(&self, other: &Self) -> Option<Ordering> {
        let lhs = self.r - self.l;
        let rhs = other.r - other.l;

        if lhs == rhs {
            return self.l.partial_cmp(&other.l);
        }

        lhs.partial_cmp(&rhs)
    }
}

impl Ord for Range {
    fn cmp(&self, other: &Self) -> Ordering {
        let lhs = self.r - self.l;
        let rhs = other.r - other.l;

        if lhs == rhs {
            return self.l.cmp(&other.l);
        }

        lhs.cmp(&rhs)
    }
}

impl Solution {
    pub fn smallest_range(nums: Vec<Vec<i32>>) -> Vec<i32> {
        let k = nums.len();
        let mut remained: Vec<usize> = nums.iter().map(|row| row.len()).collect();
        let mut flatten: Vec<_> = nums
            .iter()
            .enumerate()
            .flat_map(|(i, row)| row.iter().map(move |&val| Item::new(i, val)))
            .collect();
        flatten.sort_by(|lhs, rhs| lhs.val.cmp(&rhs.val));

        let (mut l, mut r) = (0, flatten.len() - 1);
        let mut range = Range::new(flatten[l].val, flatten[r].val);
        while l <= r {
            if remained[flatten[l].idx] > 1 {
                remained[flatten[l].idx] -= 1;
                l += 1;
                range = cmp::min(range, Range::new(flatten[l].val, flatten[r].val));
            } else if remained[flatten[r].idx] > 1 {
                remained[flatten[r].idx] -= 1;
                r -= 1;
                range = cmp::min(range, Range::new(flatten[l].val, flatten[r].val));
            } else if r - l == k {
                if l > 0 && (remained[flatten[r].idx] > 1 || flatten[l - 1].idx == flatten[r].idx) {
                    remained[flatten[r].idx] -= 1;
                    remained[flatten[l - 1].idx] += 1;
                    l -= 1;
                    r -= 1;

                    range = cmp::min(range, Range::new(flatten[l].val, flatten[r].val));
                }
            } else {
                return vec![range.l, range.r];
            }
        }

        panic!("invalid case occurred")
    }
}