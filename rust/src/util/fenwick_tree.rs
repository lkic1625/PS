// struct FenwickTree<T> {
//     inner: Vec<T>,
// }
//
// impl <T> FenwickTree<T> {
//     pub fn new(len: usize, e: T) -> FenwickTree<T> {
//         let mut inner = vec![e; len + 1];
//
//         Self {
//             inner
//         }
//     }
//
//     pub fn range_update(&mut self, l: i32, r: i32, sum: i32) {
//         Self::add(&mut self.inner, l, sum);
//         Self::add(&mut self.inner, r + 1, -sum);
//     }
//
//     pub fn point_query(&mut self, i: i32) -> i32 {
//         Self::sum(&self.inner, i)
//     }
//
//     fn sum(vec: &Vec<i32>, mut i: i32) -> i32 {
//         let mut ret = 0;
//         while i > 0 {
//             ret += vec[i];
//             i -= (i & -i);
//         }
//
//         ret
//     }
//
//     fn add(vec: &mut Vec<i32>, mut i: i32, num: i32) {
//         while i <= vec.len() as i32 {
//             vec[i] += num;
//             i += (i & -i);
//         }
//     }
// }