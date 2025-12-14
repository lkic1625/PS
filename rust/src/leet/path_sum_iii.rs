use std::collections::{HashMap, VecDeque};
use std::marker::PhantomData;
use std::os::macos::raw::stat;
use std::ptr::{null, null_mut};

struct Solution;

// Definition for a binary tree node.
#[derive(Debug, PartialEq, Eq)]
pub struct TreeNode {
    pub val: i32,
    pub left: Option<Rc<RefCell<TreeNode>>>,
    pub right: Option<Rc<RefCell<TreeNode>>>,
}

impl TreeNode {
    #[inline]
    pub fn new(val: i32) -> Self {
        TreeNode {
            val,
            left: None,
            right: None
        }
    }

    pub fn is_leaf(&self) -> bool {
        self.left.is_none() && self.right.is_none()
    }

}
use std::rc::Rc;
use std::cell::RefCell;
impl Solution {
    pub fn path_sum(root: Option<Rc<RefCell<TreeNode>>>, target_sum: i32) -> i32 {
        let mut ret = 0;
        let mut curr: i64 = 0;
        let mut map: HashMap<i64, i32> = HashMap::new();
        Self::dfs(root, target_sum, &mut ret, &mut curr, &mut map);

        ret
    }

    pub fn dfs(node_cell: Option<Rc<RefCell<TreeNode>>>, target_sum: i32, ret: &mut i32, curr: &mut i64, map: &mut HashMap<i64, i32>) {
        if let Some(node_cell) = node_cell {
            let node = node_cell.borrow();
            *curr += node.val as i64;

            if *curr == target_sum as i64 {
                *ret += 1;
            }

            *ret += *map.get(&(*curr - target_sum as i64)).unwrap_or(&0);
            *map.entry(*curr).or_insert(0) += 1;
            Self::dfs(node.left.clone(), target_sum, ret, curr, map);
            Self::dfs(node.right.clone(), target_sum, ret, curr, map);
            *map.entry(*curr).or_insert(0) -= 1;
            *curr -= node.val as i64;
        }
    }
}