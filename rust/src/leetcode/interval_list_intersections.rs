struct Item {
    val: i32,
    is_end: bool,
    idx: usize
}

impl Item {
    fn new(val: i32, is_end: bool, idx: usize) -> Self {
        Item {
            val,
            is_end,
            idx
        }
    }
}

impl Eq for Item {}

impl PartialEq<Self> for Item {
    fn eq(&self, other: &Self) -> bool {
        self.val.eq(&other.val) && self.is_end.eq(&other.is_end) && self.idx.eq(&other.idx)
    }
}

impl PartialOrd<Self> for Item {
    fn partial_cmp(&self, other: &Self) -> Option<Ordering> {
        if self.val == other.val {
            return self.is_end.partial_cmp(&other.is_end)
        }
        self.val.partial_cmp(&other.val)
    }
}

impl Ord for Item {
    fn cmp(&self, other: &Self) -> Ordering {
        if self.val == other.val {
            return self.is_end.cmp(&other.is_end)
        }
        self.val.cmp(&other.val)
    }
}

impl Solution {
    pub fn interval_intersection(first_list: Vec<Vec<i32>>, second_list: Vec<Vec<i32>>) -> Vec<Vec<i32>> {
        let mut vec = Vec::with_capacity(first_list.len() * 2 + second_list.len() * 2);
        let mut ret = Vec::new();

        for v in first_list.iter() {
            vec.push(Item::new(v[0], false, 0));
            vec.push(Item::new(v[1], true, 0));
        }

        for v in second_list.iter() {
            vec.push(Item::new(v[0], false, 1));
            vec.push(Item::new(v[1], true, 1));
        }

        vec.sort();

        let mut first = 0;
        let mut second = 0;
        let mut temp = Item::new(-1, false, 3);
        let mut bef = &temp;
        for item in vec.iter() {
            if bef.val <= item.val && !bef.is_end && item.is_end {
                if bef.idx != item.idx {
                    ret.push(vec![bef.val, item.val]);
                } else {
                    if item.idx == 0 && second > 0 {
                        ret.push(vec![bef.val, item.val]);
                    } else if item.idx == 1 && first > 0 {
                        ret.push(vec![bef.val, item.val]);
                    }
                }
            }

            if item.is_end {
                if item.idx == 0 {
                    first -= 1;
                } else {
                    second -= 1;
                }
            } else {
                if item.idx == 0 {
                    first += 1;
                } else {
                    second += 1;
                }
            }
            bef = item;
        }

        ret
    }
}