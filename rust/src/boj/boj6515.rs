// use std::cmp;
// use std::collections::Bound::Unbounded;
//
// pub struct Boj6515<C, T> {
//     seg_tree: SegTree<fn(u32, u32) -> u32, (u32, u32)>
// }
//
// impl <C, T> Boj6515<C, T>
//     where
//         T: Copy
// {
//
//     pub fn new(vec: Vec<(u32, u32)>) -> Self {
//         Boj6515 {
//             seg_tree: SegTree::new(vec.len(), (0, 0), cmp::max, vec.iter().map(|&x| x))
//         }
//     }
//
//     fn solve(&mut self, left: usize, right: usize) -> u32 {
//         let look_up = self.seg_tree.query(left..=right);
//         let left_padded = look_up.1 - left as u32 + 1;
//         return if left_padded < look_up.0 {
//             if look_up.1 < right as u32 {
//                 let candidate = self.seg_tree.query((look_up.1 + 1) as usize..=right);
//                 cmp::max(left_padded, candidate.0)
//             } else {
//                 left_padded
//             }
//         } else {
//             look_up.0
//         };
//     }
// }
//
// pub struct SegTree<C, T> {
//     e: T,
//     v: Vec<T>,
//     offset: usize,
//     n: usize,
//     combine: C
// }
//
// impl<C, T> SegTree<C, T>
//     where
//         T: Copy,
//         C: Fn(T, T) -> T,
// {
//     fn new<I>(n: usize, e: T, combine: C, init: I) -> Self
//         where
//             I: IntoIterator<Item = T>,
//     {
//         let offset = n;
//         let mut v = vec![e; offset];
//         v.extend(init.into_iter().take(n));
//         v.resize(offset * 2, e);
//         for i in (1..offset).rev() {
//             v[i] = combine(v[i << 1], v[i << 1 | 1]);
//         }
//         Self {
//             e,
//             v,
//             offset,
//             n,
//             combine
//         }
//     }
//
//     fn query<B: std::ops::RangeBounds<usize>>(&self, range: B) -> T {
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
//         let mut lsum = self.e;
//         let mut rsum = self.e;
//         while l < r {
//             if l & 1 != 0 {
//                 lsum = (self.combine)(lsum, self.v[l]);
//                 l += 1;
//             }
//             if r & 1 != 0 {
//                 r -= 1;
//                 rsum = (self.combine)(self.v[r], rsum);
//             }
//             l >>= 1;
//             r >>= 1;
//         }
//         (self.combine)(lsum, rsum)
//     }
// }