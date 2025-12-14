use std::cmp::Reverse;
use std::collections::BinaryHeap;

struct MedianFinder {
    left: BinaryHeap<i32>,
    right: BinaryHeap<Reverse<i32>>,
}

impl MedianFinder {
    fn new() -> Self {
        MedianFinder {
            left: BinaryHeap::new(),
            right: BinaryHeap::new(),
        }
    }

    fn add_num(&mut self, num: i32) {
        self.left.push(num);
        self.right.push(Reverse(self.left.pop().unwrap()));
        if self.left.len() < self.right.len() {
            self.left.push(self.right.pop().unwrap().0);
        }
    }

    fn find_median(&self) -> f64 {
        let len = self.left.len() + self.right.len();
        if len % 2 == 0 {
            (self.left.peek().unwrap() + self.right.peek().unwrap().0) as f64 / 2f64
        } else {
            *self.left.peek().unwrap() as f64
        }
    }
}
