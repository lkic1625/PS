struct FenwickTree {
    inner: Vec<i32>,
}

impl FenwickTree {
    pub fn new(len: usize) -> FenwickTree {
        let mut inner = vec![0; len + 1];

        Self {
            inner
        }
    }

    pub fn range_update(&mut self, l: i32, r: i32, sum: i32) {
        Self::add(&mut self.inner, l, sum);
        Self::add(&mut self.inner, r + 1, -sum);
    }

    pub fn point_query(&mut self, i: i32) -> i32 {
        Self::sum(&self.inner, i)
    }

    fn sum(vec: &Vec<i32>, mut i: i32) -> i32 {
        let mut ret = 0;
        while i > 0 {
            ret += vec[i as usize];
            i -= (i & -i);
        }

        ret
    }

    fn add(vec: &mut Vec<i32>, mut i: i32, num: i32) {
        while i < vec.len() as i32 {
            vec[i as usize] += num;
            i += (i & -i);
        }
    }
}

struct CustomStack {
    maxSize: i32,
    len: i32,
    inner: FenwickTree,
}

/**
 * `&self` means the method takes an immutable reference.
 * If you need a mutable reference, change it to `&mut self` instead.
 */
impl CustomStack {

    fn new(maxSize: i32) -> Self {
        Self {
            maxSize,
            len: 0,
            inner: FenwickTree::new(maxSize as usize)
        }
    }

    fn push(&mut self, x: i32) {
        if self.len == self.maxSize {
            return;
        }

        self.len += 1;
        self.inner.range_update(self.len, self.len, x);
    }

    fn pop(&mut self) -> i32 {
        if self.len == 0 {
            return -1;
        }

        let val = self.inner.point_query(self.len);
        self.inner.range_update(self.len, self.len, -val);
        self.len -= 1;

        val
    }

    fn increment(&mut self, k: i32, val: i32) {
        let left = 1;
        let mut right = left + k - 1;
        if right > self.len {
            right = self.len;
        }
        self.inner.range_update(left, right, val);
    }
}


/**
 * Your CustomStack object will be instantiated and called as such:
 * let obj = CustomStack::new(maxSize);
 * obj.push(x);
 * let ret_2: i32 = obj.pop();
 * obj.increment(k, val);
 */