use std::collections::Bound::Unbounded;
use std::ops::AddAssign;

pub struct Boj12858 {
    vec: Vec<i64>,
    queries: Vec<(i64, usize, usize)>
}

impl Boj12858 {
    fn new(vec: Vec<i64>, queries: Vec<(i64, usize, usize)>) -> Self {
        Boj12858 {
            vec,
            queries,
        }
    }

    fn solve(&mut self) {
        let n = self.vec.len();
        let mut diff_vec = self.vec.windows(2).map(|win| (win[0] - win[1]).abs()).collect::<Vec<_>>();
        let mut gcd_seg_tree = SegTree::new(
            n - 1,
            0,
            gcd,
            |a:&mut i64, b| *a = b,
            diff_vec.iter().map(|&x| x)
        );
        let mut lazy_seg_tree = LazySegTree::new(
            n,
            0,
            |a:&mut i64, b| *a += b,
            self.vec.iter().map(|&x| x)
        );

        for &(t, left, right) in &self.queries {
            match t {
                0 => {
                    let mut result = gcd_seg_tree.query(left..right);
                    result = gcd(lazy_seg_tree.point_query(left), result);
                    print!("{}", result);
                },
                _ => {
                    lazy_seg_tree.update_range(left..=right, t);
                    if left >= 1 {
                        let l = lazy_seg_tree.point_query(left - 1) - lazy_seg_tree.point_query(left);
                        gcd_seg_tree.update(left - 1, l.abs());
                    }
                    if right < n - 1 {
                        let r = lazy_seg_tree.point_query(right) - lazy_seg_tree.point_query(right + 1);
                        gcd_seg_tree.update(right, r.abs());
                    }
                }
            }
        }
    }
}

fn gcd(mut a: i64, mut b: i64) -> i64 {
    while b != 0 {
        let temp = b;
        b = a % b;
        a = temp;
    }
    a
}

pub struct SegTree<C, A, T> {
    e: T,
    v: Vec<T>,
    offset: usize,
    n: usize,
    combine: C,
    apply: A,
}

impl<C, A, T> SegTree<C, A, T>
    where
        T: Copy + PartialEq,
        C: Fn(T, T) -> T,
{
    fn new<I>(n: usize, e: T, combine: C, apply: A, init: I) -> Self
        where
            I: IntoIterator<Item = T>,
    {
        let offset = n;
        let mut v = vec![e; offset];
        v.extend(init.into_iter().take(n));
        for i in (1..offset).rev() {
            v[i] = combine(v[i << 1], v[i << 1 | 1]);
        }
        Self { e, v, offset, n, combine, apply, }
    }

    fn query<B: std::ops::RangeBounds<usize>>(&self, range: B) -> T {
        use std::ops::Bound::*;
        let mut l = self.offset + match range.start_bound() {
            Included(&x) => x,
            Excluded(&x) => x + 1,
            Unbounded => 0,
        };
        let mut r = self.offset + match range.end_bound() {
            Included(&x) => x + 1,
            Excluded(&x) => x,
            Unbounded => self.n,
        };
        let mut sum = self.e;
        while l < r {
            if l & 1 != 0 {
                sum = (self.combine)(sum, self.v[l]);
                l += 1;
            }
            if r & 1 != 0 {
                r -= 1;
                sum = (self.combine)(self.v[r], sum);
            }
            l >>= 1;
            r >>= 1;
        }
        sum
    }

    fn update<U>(&mut self, mut i: usize, u: U) where U: Copy, A: Fn(&mut T, U), {
        i += self.offset;
        (self.apply)(&mut self.v[i], u);
        while i > 1 {
            i >>= 1;
            self.v[i] = (self.combine)(self.v[i << 1], self.v[i << 1 | 1]);
        }
    }
}

/// This is not a complete implementation of LazySegTree.
pub struct LazySegTree<A, T> {
    e: T,
    v: Vec<T>,
    lazy: Vec<T>,
    offset: usize,
    n: usize,
    apply: A,
}

impl<A, T> LazySegTree<A, T>
    where
        T: Copy + AddAssign + PartialEq,
{
    fn new<I>(n: usize, e: T, apply: A, init: I) -> Self where I: IntoIterator<Item = T>, {
        let offset = n;
        let mut v: Vec<T> = vec![e; offset];
        v.extend(init.into_iter().take(n));
        Self { e, v, lazy: vec![e; offset * 2], offset, n, apply, }
    }

    fn point_query(&mut self, i: usize) -> T where A: Fn(&mut T, T) {
        let mut path = std::iter::successors(Some(i + self.offset), |&node| Some(node >> 1))
            .take_while(|&node| node >= 1)
            .collect::<Vec<_>>();
        path.iter().rev().for_each(|&node| self.propagate(node));

        self.v[i + self.offset]
    }

    fn update_range<B: std::ops::RangeBounds<usize>>(&mut self, range: B, u: T)
        where
            A: Fn(&mut T, T)
    {
        use std::ops::Bound::*;
        let mut l = self.offset + match range.start_bound() {
            Included(&x) => x,
            Excluded(&x) => x + 1,
            Unbounded => 0,
        };
        let mut r = self.offset + match range.end_bound() {
            Included(&x) => x + 1,
            Excluded(&x) => x,
            Unbounded => self.n,
        };
        while l < r {
            if l & 1 != 0 {
                self.propagate(l);
                self.lazy[l] += u;
                l += 1;
            }
            if r & 1 != 0 {
                r -= 1;
                self.propagate(r);
                self.lazy[r] += u;
            }
            l >>= 1;
            r >>= 1;
        }
    }

    /// propagate the lazy value to the children
    /// but this method can only update the value of leaf nodes.
    fn propagate(&mut self, i: usize) where A: Fn(&mut T, T) {
        if self.lazy[i] != self.e {
            let lazy= self.lazy[i];
            if i < self.offset {
                self.lazy[i << 1] += lazy;
                self.lazy[i << 1 | 1] += lazy;
            } else {
                (self.apply)(&mut self.v[i], lazy);
            }
            self.lazy[i] = self.e;
        }
    }
}