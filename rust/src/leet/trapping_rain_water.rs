use std::cmp;

struct MonotoneStack {
    inner: Vec<i32>,
    water: i32,
}

impl MonotoneStack {
    fn new(inner: Vec<i32>) -> MonotoneStack {
        Self {
            inner,
            water: 0
        }
    }

    fn push(&mut self, item: i32) {
        if !self.is_empty() && self.peek() < item {
            let water = self.pop_until_monotone(item);
            println!("{}", water);
            self.water += water;
        }
        self.inner.push(item);
    }

    fn peek(&self) -> i32 {
        *self.inner.last().unwrap()
    }

    fn pop(&mut self) -> i32 {
        self.inner.pop().unwrap()
    }

    fn is_empty(&self) -> bool {
        self.inner.is_empty()
    }

    pub fn pop_until_monotone(&mut self, threshold: i32) -> i32 {
        let (mut ret, mut buffer, mut infimum) = (0, Vec::new(), 0);
        while !self.is_empty() && threshold >= self.peek() {
            let pop = self.pop();
            infimum = cmp::max(pop, infimum);
            buffer.push(pop);
        }

        infimum = cmp::max(self.peek(), infimum);

        let water = cmp::min(infimum, threshold);
        for block in buffer.iter() {
            ret += water - block;
        }

        if !self.is_empty() {
            self.inner.extend(vec![water; buffer.len()]);
        }

        ret
    }
}


impl Solution {
    pub fn trap(height: Vec<i32>) -> i32 {
        // vec![0,1,0,2,1,0,1,3,2,1,2,1];
        let mut ms = MonotoneStack::new(Vec::with_capacity(height.len()));

        height.iter().for_each(|i| ms.push(*i));

        ms.water
    }
}