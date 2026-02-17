//! # RLE Iterator
//!
//! - Platform: LeetCode
//! - Number: 936
//! - Difficulty: Medium
//! - URL: https://leetcode.com/problems/rle-iterator/
//! - Tags: Array,Design,Counting,Iterator

// We can use run-length encoding (i.e., RLE) to encode a sequence of integers. In a run-length encoded array of even length encoding (0-indexed), for all even i, encoding[i] tells us the number of times that the non-negative integer value encoding[i + 1] is repeated in the sequence.

// For example, the sequence arr = [8,8,8,5,5] can be encoded to be encoding = [3,8,2,5]. encoding = [3,8,0,9,2,5] and encoding = [2,8,1,8,2,5] are also valid RLE of arr.
// Given a run-length encoded array, design an iterator that iterates through it.

// Implement the RLEIterator class:

// RLEIterator(int[] encoded) Initializes the object with the encoded array encoded.
// int next(int n) Exhausts the next n elements and returns the last element exhausted in this way. If there is no element left to exhaust, return -1 instead.
// pub struct Solution;

struct RLEIterator {
    vec: Vec<i32>,
    idx: usize,
}

/**
 * `&self` means the method takes an immutable reference.
 * If you need a mutable reference, change it to `&mut self` instead.
 */
impl RLEIterator {
    fn new(encoding: Vec<i32>) -> Self {
        Self {
            vec: encoding,
            idx: 0,
        }
    }

    fn next(&mut self, n: i32) -> i32 {
        let mut remain = n;

        while remain > 0 {
            if self.idx >= self.vec.len() {
                return -1;
            }
            if self.vec[self.idx] > 0 {
                if self.vec[self.idx] > remain {
                    self.vec[self.idx] -= remain;
                    return self.vec[self.idx + 1];
                } else if self.vec[self.idx] == remain {
                    self.idx += 2;
                    return self.vec[self.idx - 1];
                } else {
                    remain -= self.vec[self.idx];
                    self.idx += 2;
                }
            } else {
                self.idx += 2;
            }
        }

        -1
    }
}

/**
 * Your RLEIterator object will be instantiated and called as such:
 * let obj = RLEIterator::new(encoding);
 * let ret_1: i32 = obj.next(n);
 */

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn test_example() {
        // LeetCode Example: encoding = [3,8,2,5], sequence = [8,8,8,5,5]
        let mut iter = RLEIterator::new(vec![3, 8, 2, 5]);
        assert_eq!(iter.next(2), 8); // exhaust 2 of [8,8,8,5,5] -> return 8
        assert_eq!(iter.next(1), 8); // exhaust 1 of [8,5,5] -> return 8
        assert_eq!(iter.next(1), 5); // exhaust 1 of [5,5] -> return 5
        assert_eq!(iter.next(2), -1); // exhaust 2 of [5] -> not enough, return -1
    }

    #[test]
    fn test_exact_exhaustion() {
        // Exhaust exactly all elements at once
        let mut iter = RLEIterator::new(vec![3, 8, 2, 5]);
        assert_eq!(iter.next(5), 5); // exhaust all 5 elements, last is 5
        assert_eq!(iter.next(1), -1); // no elements left
    }

    #[test]
    fn test_with_zero_count() {
        // encoding = [3,8,0,9,2,5] -> sequence = [8,8,8,5,5] (0 nines)
        let mut iter = RLEIterator::new(vec![3, 8, 0, 9, 2, 5]);
        assert_eq!(iter.next(3), 8); // exhaust 3 eights
        assert_eq!(iter.next(1), 5); // skip zero 9s, get first 5
        assert_eq!(iter.next(1), 5); // get second 5
        assert_eq!(iter.next(1), -1); // no more elements
    }

    #[test]
    fn test_single_element() {
        let mut iter = RLEIterator::new(vec![1, 42]);
        assert_eq!(iter.next(1), 42);
        assert_eq!(iter.next(1), -1);
    }

    #[test]
    fn test_large_skip() {
        // encoding = [5, 1, 3, 2] -> sequence = [1,1,1,1,1,2,2,2]
        let mut iter = RLEIterator::new(vec![5, 1, 3, 2]);
        assert_eq!(iter.next(6), 2); // skip 5 ones and 1 two -> return 2
        assert_eq!(iter.next(2), 2); // exhaust remaining 2 twos -> return 2
        assert_eq!(iter.next(1), -1);
    }

    #[test]
    fn test_empty_after_exhaustion() {
        let mut iter = RLEIterator::new(vec![2, 7]);
        assert_eq!(iter.next(1), 7);
        assert_eq!(iter.next(1), 7);
        assert_eq!(iter.next(1), -1);
        assert_eq!(iter.next(1), -1); // still -1
    }

    #[test]
    fn test_multiple_groups() {
        // encoding = [1,1,1,2,1,3,1,4] -> sequence = [1,2,3,4]
        let mut iter = RLEIterator::new(vec![1, 1, 1, 2, 1, 3, 1, 4]);
        assert_eq!(iter.next(1), 1);
        assert_eq!(iter.next(1), 2);
        assert_eq!(iter.next(1), 3);
        assert_eq!(iter.next(1), 4);
        assert_eq!(iter.next(1), -1);
    }

    #[test]
    fn test_zero_count_with_partial_exhaust() {
        // [[[3,8,0,9,2,5]],[2],[1],[1],[2]]
        // encoding = [3,8,0,9,2,5] -> sequence = [8,8,8,5,5] (0 nines)
        let mut iter = RLEIterator::new(vec![3, 8, 0, 9, 2, 5]);
        assert_eq!(iter.next(2), 8); // exhaust 2 of [8,8,8,5,5] -> return 8
        assert_eq!(iter.next(1), 8); // exhaust 1 of [8,5,5] -> return 8
        assert_eq!(iter.next(1), 5); // exhaust 1 of [5,5] -> return 5
        assert_eq!(iter.next(2), -1); // exhaust 2 of [5] -> not enough, return -1
    }
}