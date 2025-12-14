use std::cmp;
use crate::util::solvable::Solvable;

pub struct Boj1689 {
    n: u32,
    vec: Vec<(i32, bool)>,
    counter: u32
}

impl Boj1689 {
    pub fn new(n: u32, vec: Vec<(i32, bool)>) -> Self {
        Boj1689 {
            n,
            vec,
            counter: 0u32
        }
    }
}

impl Solvable<u32> for Boj1689 {
    fn solve(&mut self) -> u32 {
        self.vec.sort_unstable_by(|a, b| {
            if a.0 == b.0 {
                a.1.cmp(&b.1)
            } else {
                a.0.cmp(&b.0)
            }
        });

        let mut max = 0;
        for tuple in self.vec.iter() {
            if tuple.1 {
                self.counter += 1;
            } else {
                self.counter -= 1;
            }

            max = cmp::max(max, self.counter);
        }

        max
    }
}