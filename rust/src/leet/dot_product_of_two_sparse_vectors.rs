use std::collections::LinkedList;

struct Node {
    val: i32,
    idx: usize
}

struct SparseVector {
    inner: LinkedList<Node>
}

/**
 * `&self` means the method takes an immutable reference.
 * If you need a mutable reference, change it to `&mut self` instead.
 */
impl SparseVector {
    fn new(nums: Vec<i32>) -> Self {
        let mut inner = LinkedList::new();
        let mut idx = 0;
        let mut bef = -1;
        for i in nums {
            if i != 0 && bef == 0 {
                inner.push_back(Node {
                    val: 0,
                    idx: idx - 1
                });
            }

            if i != 0 {
                inner.push_back(Node {
                    val: i,
                    idx
                });
            }

            idx += 1;
            bef = i;
        }

        Self {
            inner
        }
    }

    // Return the dotProduct of two sparse vectors
    fn dot_product(&self, vec: SparseVector) -> i32 {
        let mut lhs = self.inner.iter();
        let mut rhs = vec.inner.iter();

        let mut idx = 0;
        let mut ret = 0;

        let l = lhs.next();
        let r = rhs.next();
        if l.is_none() || r.is_none() {
            return ret;
        }

        let mut l = l.unwrap();
        let mut r = r.unwrap();

        while true {
            if l.idx == r.idx {
                ret += l.val * r.val;
                let op_l = lhs.next();
                let op_r = rhs.next();
                if op_l.is_none() || op_r.is_none() {
                    return ret;
                }
                l = op_l.unwrap();
                r = op_r.unwrap();
            } else if l.idx < r.idx {
                while l.idx < r.idx {
                    let op_l = lhs.next();
                    if op_l.is_none() {
                        return ret;
                    }

                    l = op_l.unwrap();
                }
            } else if l.idx > r.idx {
                while l.idx > r.idx {
                    let op_r = rhs.next();
                    if op_r.is_none() {
                        return ret;
                    }

                    r = op_r.unwrap();
                }
            }
        }

        panic!("an invalid case occurred.")
    }
}