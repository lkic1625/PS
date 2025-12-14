// use std::collections::Bound::Unbounded;
// use std::ops::AddAssign;
//
// /// Segment Tree with Lazy Propagation.
// /// This is non-reculsive version of segment tree.
// /// This implementation is based on the following article:
// /// https://www.acmicpc.net/blog/view/117
// pub struct LazySegTree<C, A, T> {
//     e: T,
//     v: Vec<T>,
//     lazy: Vec<T>,
//     offset: usize,
//     n: usize,
//     apply: A,
//     combine: C,
//     height: usize
// }
//
// impl<C, A, T> LazySegTree<C, A, T>
//     where
//         T: Copy + AddAssign + PartialEq,
//         C: Fn(T, T) -> T,
// {
//     fn new<I>(n: usize, e: T, apply: A, combine: C, init: I) -> Self where I: IntoIterator<Item = T>, {
//         let offset = n;
//         let mut v: Vec<T> = vec![e; offset];
//         v.extend(init.into_iter().take(n));
//         for i in (1..offset).rev() {
//             v[i] = combine(v[i << 1], v[i << 1 | 1]);
//         }
//         Self { e, v, lazy: vec![e; offset * 2], offset, n, apply, combine, height: Self::next_power_of_2(n) }
//     }
//
//     fn next_power_of_2(n: usize) -> usize {
//         let mut result = 1;
//         while result < n {
//             result <<= 1;
//         }
//         result
//     }
//
//     fn query<B: std::ops::RangeBounds<usize>>(&mut self, range: B) -> T {
//         use std::ops::Bound::*;
//         let mut l = self.offset
//             + match range.start_bound() {
//             Included(&x) => x,
//             Excluded(&x) => x + 1,
//             Unbounded => 0,
//         };
//         let mut r = self.offset
//             + match range.end_bound() {
//             Included(&x) => x + 1,
//             Excluded(&x) => x,
//             Unbounded => self.n,
//         };
//
//         let mut path = Vec::new();
//         while l < r {
//             if l & 1 != 0 {
//                 path.push(l);
//                 l += 1;
//             }
//             if r & 1 != 0 {
//                 r -= 1;
//                 path.push(r);
//             }
//             l >>= 1;
//             r >>= 1;
//         }
//         let mut sum = self.e;
//         path.iter().rev().for_each(|&node| {
//             self.propagate(node);
//             sum += self.v[node];
//         });
//     }
//
//     fn point_query(&mut self, i: usize) -> T where A: Fn(&mut T, T) {
//         let mut path = std::iter::successors(Some(i + self.offset), |&node| Some(node >> 1))
//             .take_while(|&node| node >= 1)
//             .collect::<Vec<_>>();
//         path.iter().rev().for_each(|&node| self.propagate(node));
//
//         self.v[i + self.offset]
//     }
//
//     fn update_range<B: std::ops::RangeBounds<usize>>(&mut self, range: B, u: T)
//         where
//             A: Fn(&mut T, T)
//     {
//         use std::ops::Bound::*;
//         let mut l = self.offset + match range.start_bound() {
//             Included(&x) => x,
//             Excluded(&x) => x + 1,
//             Unbounded => 0,
//         };
//         let mut r = self.offset + match range.end_bound() {
//             Included(&x) => x + 1,
//             Excluded(&x) => x,
//             Unbounded => self.n,
//         };
//
//         for i in (1..=self.height).rev() {
//             if l >> i << i != l {
//                 self.propagate(i);
//             }
//             if r + 1 >> i << i != r + 1 {
//                 self.propagate(i);
//             }
//         }
//
//         while l < r {
//             if l & 1 != 0 {
//
//                 l += 1;
//             }
//             if r & 1 != 0 {
//                 r -= 1;
//                 self.propagate(r);
//                 self.lazy[r] += u;
//             }
//             l >>= 1;
//             r >>= 1;
//         }
//     }
//
//     /// propagate the lazy value to the children
//     /// but this method can only update the value of leaf nodes.
//     fn propagate(&mut self, i: usize) where A: Fn(&mut T, T) {
//         if self.lazy[i] != self.e {
//             let lazy= self.lazy[i];
//             if i < self.offset {
//                 self.lazy[i << 1] += lazy;
//                 self.lazy[i << 1 | 1] += lazy;
//             }
//             (self.apply)(&mut self.v[i], lazy);
//             self.lazy[i] = self.e;
//         }
//     }
// }